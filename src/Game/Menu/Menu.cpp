#include <iostream>
#include <climits>
#include <functional>
#include "Menu.h"
#include "../GameManager.h"

Menu::Menu(GameManager * g, GUI * gui, GameSaver * gs) {
    this->gui = gui;
    this->g = g;
    this->gs = gs;
    items = std::vector<MenuItem>{
        MenuItem("Play with your friend",std::vector<int>{},"",[=](){optStartFriendGame();}),
        MenuItem("Play against computer",std::vector<int>{}, "", [=](){optStartAIGame();}),
        MenuItem("Load game","Please type the name of the save below:\nIf you want to go back, type \"q\".",[=](std::string str,std::string * out){return loadWrapper(str,out);}),
        MenuItem("Exit",std::vector<int>{}),
        MenuItem("Go to Main Menu",std::vector<int>{0,1,2,3}, "Welcome to Hearthstone C++ edition, choose your action:"),

        MenuItem("Go back",std::vector<int>{},"",[](){}),

        //player turn actions
        MenuItem("PlayerTurnAction",std::vector<int>{7,8,9,10,11}, "Player %player% is playing, choose your action:"),
        MenuItem("Attack with minion",std::vector<int>{}, "",[=](){prepareSelectAttackersMenu();}),
        MenuItem("Play card",std::vector<int>{}, "",[=](){preparePlayCardMenu();}),
        MenuItem("End turn",std::vector<int>{}, "",[=](){
            g->nextTurn();
            if (g->isFinished())
                selectedItem = 12;
            draw();}),
        MenuItem("Save game","Please type the name of the save\nIf you want to go back, type \"q\".",[=](std::string str, std::string * out ){return saveWrapper(str,out);}),
        MenuItem("Exit",std::vector<int>{}),

        MenuItem("EndGame", std::vector<int>{3},"Player %player% won, thank you for playing!")
    };

}



void Menu::drawStringInput(std::string header,std::function<bool(std::string,std::string * out)> f) {
    clearScreen();
    std::cout << header << std::endl;
    std::string str;
    std::cout << "Name: ";
    while (true) {
        if (std::cin >> str) {
            if (str == "q") {
                return;
            }
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }
            std::string msg;
            if (f(str,&msg)) {
                break;
            } else {
                std::cout << msg << std::endl;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        }
    }
}

void Menu::preparePlayCardMenu() {
    std::vector<std::string> s;
    const std::vector<Card*> * hand = g->getCurrentPlayer()->getHand();
    for (int i = 0; i < (int)hand->size(); i++) {
        s.push_back(hand->at(i)->print());
    }
    s.push_back("Go back");
    std::function<void(int)> f = [=](int a){playCard(a);};
    draw(s,"Select card from your hand:",f);
}

void Menu::prepareSelectAttackersMenu() {
    std::vector<std::string> s;
    std::vector<Minion*> attackers = g->getBoard()->availableAttackers();
    for (int i = 0; i < (int)attackers.size(); i++) {
        s.push_back(attackers.at(i)->print());
    }
    s.push_back("Go back");
    std::function<void(int)> f = [=](int a){prepareSelectTargetsMenu(a);};
    draw(s,"Select minion to attack with:",f);
}

void Menu::prepareSelectTargetsMenu(int minion) {
    if ((int)g->getBoard()->availableAttackers().size() == minion) {
        draw();
        return;
    }
    std::vector<std::string> s;
    std::vector<Entity*> attackers = g->getBoard()->availableTargets();
    for (int i = 0; i < (int)attackers.size(); i++) {
        s.push_back(attackers.at(i)->print());
    }
    s.push_back("Go back");
    selectedAttacker = minion;
    std::function<void(int)> f = [=](int a){attack(a);};
    draw(s,"Select target to attack to:",f);
}

void Menu::draw() {
    MenuItem * m = &items[selectedItem];
    clearScreen();

    gui->draw(g);


    drawHeader(m->header);

    //drawing the menu items with indexes
    for (int i = 0; i < (int)m->ref.size(); i++){
        std::cout << i+1 << ". " << items[m->ref[i]].value << std::endl;
    }

    int output;
    readMenuInput(&output,(int)m->ref.size());
    int index = m->ref[output];
    if (items[index].func != nullptr) {
        items[index].func();
    }
    if (items[index].strInputFunc != nullptr) {
        drawStringInput(items[index].header,items[index].strInputFunc);
        draw();
    }
    lastItem = selectedItem;
    selectedItem = index;

}

void Menu::draw(std::vector<std::string> s,std::string header,std::function<void(int)> f) {
    clearScreen();
    gui->draw(g);
    std::cout << header << std::endl;
    for (int i = 0; i < (int)s.size(); i++){
        std::cout << i+1 << ". " << s.at(i) << std::endl;
    }
    int output;
    readMenuInput(&output,(int)s.size());
    if (f != nullptr)
        f(output);
}

void Menu::readMenuInput(int * out, int arrSize) {
    int o = -1;
    if (msg != "") {
        std::cout << msg << std::endl;
        msg = "";
    }
    //waiting for an user input
    while (true) {
        std::cout << "Your choice: ";
        if (std::cin >> o) {
            if (o > 0 && o <= arrSize)
                break;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    *out = o-1;
}

void Menu::optStartFriendGame() {
    g->startGame();
    selectedItem = 6;

    draw();
}

void Menu::playCard(int optIndex) {
    const std::vector<Card*> * hand = g->getCurrentPlayer()->getHand();
    if (optIndex != (int)hand->size()) {
        if (!g->playCard(optIndex)) {
            msg = "The card you selected wasn't played.\n(maybe you just don't have enough mana)";
        }
    }
    draw();
}

void Menu::clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

void Menu::attack(int targetIndex) {
    if (targetIndex == (int)g->getBoard()->availableTargets().size()) {
        prepareSelectAttackersMenu();
        return;
    }
    Entity * attacker = g->getBoard()->availableAttackers().at(selectedAttacker);
    Entity * target = g->getBoard()->availableTargets().at(targetIndex);

    bool playerWasKilled = false;
    bool res = g->getBoard()->attackTo(attacker,target,*g->getTurn(),&playerWasKilled);
    if (!res) {
        msg = "Attack wasn't successful.\n(before attacking you need to wait a turn)";
    } else if (res && playerWasKilled){
        g->setGameFinished();
        selectedItem = 12;
    }
    draw();
}

bool Menu::loadWrapper(std::string path, std::string *out) {
    bool res = gs->loadGame(path,&this->g);
    if (res) {
        msg = "Game was loaded successfully.";
        selectedItem = 6;
        //draw();
    } else {
        *out = "There is a problem with loading that savegame.";
    }
    return res;
}

bool Menu::saveWrapper(std::string path, std::string * out) {
    bool res = gs->saveGame(path,this->g);
    if (res) {
        msg = "Game was successfully saved.";
    } else {
        *out = "There was an error with saving the game.";
    }
    return res;
}

void Menu::optStartAIGame() {
    g->startGame(true);
    selectedItem = 6;

    draw();
}

void Menu::drawHeader(std::string header) {
    size_t found = header.find("%player%");
    if (found != std::string::npos)
        header.replace(found,8,std::to_string(g->getAnotherPlayerIndex()+1));
    std::cout << header << std::endl;
}
