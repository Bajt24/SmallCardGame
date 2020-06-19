#ifndef PA2_HEARTHSTONE_MENU_H
#define PA2_HEARTHSTONE_MENU_H


#include <string>
#include <vector>
#include <functional>
#include "MenuItem.h"
#include "../GUI.h"
#include "../GameManager.h"
#include "../GameSaver.h"
/**
 * Class that provides control of Game
 */
class Menu {
public:
    /** Constructor which contains pointers to GameManager, GUI and GameSaver */
    Menu(GameManager * g, GUI * gui, GameSaver * gs);
    /** Function that draws menu onto screen */
    void draw();
private:
    GUI * gui;
    GameManager * g;
    GameSaver * gs;
    std::vector<MenuItem> items;
    int selectedItem = 4;
    int lastItem = 0;
    std::string msg = "";

    int selectedAttacker;
    void clearScreen();
    /** Draw function that takes function as parameter that is called whenever we select this item from menu*/
    void draw(std::vector<std::string> s,std::string header,std::function<void(int)> f);
    /** Takes care of text input from keyboard which is used for entering file names*/
    void drawStringInput(std::string header,std::function<bool(std::string, std::string * out)> f);
    /** Draws card in out hand to the screen */
    void preparePlayCardMenu();
    void playCard(int optIndex);
    /** Sets up game for two players*/
    void optStartFriendGame();
    void optStartAIGame();
    void readMenuInput(int * out, int arrSize);
    /** Draws available minions that can attack*/
    void prepareSelectAttackersMenu();
    /** It is called whenever we want to attack with entity and takes the target index*/
    void attack(int targetIndex);
    /** Shows available targets*/
    void prepareSelectTargetsMenu(int minion);
    /** Prints the menu header */
    void drawHeader(std::string header);


    /** Function that wraps the save game process of GameSaver*/
    bool saveWrapper(std::string path, std::string * out);
    /** Function that wraps the load game process of GameSaver*/
    bool loadWrapper(std::string path, std::string * out);
};


#endif //PA2_HEARTHSTONE_MENU_H
