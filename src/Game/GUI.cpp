#include <sstream>
#include <iostream>
#include "GUI.h"
#include "GameManager.h"


void GUI::draw(GameManager * g) {
    this->p1 = g->getCurrentPlayer();
    this->p2 = g->getAnotherPlayer();
    this->b = g->getBoard();
    this->turn = g->getTurn();
    std::stringstream ss;
    //p1 means current player, p2 the opponent

    drawPlayer(&ss,p2);
    drawMinions(&ss,b->getAnotherBoard());
    drawMiddleLine(&ss);
    drawMinions(&ss,b->getCurrentBoard());
    drawPlayer(&ss,p1);

    std::cout << ss.str();
}

void GUI::drawPlayer(std::stringstream *ss, Player * p) {
    std::stringstream s,f;
    s << "| " << p->getHealth() << "HP, " << (int)p->getHand()->size() << " cards, "<<p->getMana()<<"/"<<p->getMaxMana()<<" mana |";
    int spaces = windowScale / 2 - (int)s.str().size()/2;
    printSpaces(spaces,&f);
    *ss << f.str() << s.str() << std::endl;
}

void GUI::drawMinions(std::stringstream *ss, std::vector<Minion*>* a) {
    if (a->size() == 0) {
        *ss<<std::endl<<std::endl<<std::endl;
        return;
    }

    int spaceBetweenMinions = (windowScale - (b->boardSize*3))/(b->boardSize-1);
    int totalSpace = ((int)a->size()-1)*spaceBetweenMinions + (int)a->size()*3;

    drawMinionsHead(ss,a,totalSpace,spaceBetweenMinions);
    drawMinionsBody(ss,a,totalSpace,spaceBetweenMinions);
    drawMinionsStats(ss,a,totalSpace,spaceBetweenMinions);

    *ss<<std::endl;
}

void GUI::printSpaces(int num, std::stringstream * s) {
    for (int i = 0; i < num; i++) {
        *s << " ";
    }
}

void GUI::drawMinionsHead(std::stringstream *ss, std::vector<Minion *> *a, int totalSpace, int spaceMeziMinionama) {
    printSpaces(windowScale/2 - totalSpace/2,ss);
    for (int i = 0; i < (int)a->size(); i++) {
        *ss << " _ ";
        if (i != (int)a->size() -1) {
            printSpaces(spaceMeziMinionama,ss);
        }
    }
    printSpaces(windowScale/2 - totalSpace/2,ss);
    *ss<<"||"<<std::endl;
}

void GUI::drawMinionsBody(std::stringstream *ss, std::vector<Minion *> *a, int totalSpace, int spaceMeziMinionama) {
    printSpaces(windowScale/2 - totalSpace/2,ss);
    for (int i = 0; i < (int)a->size(); i++) {
        *ss << "|";
        if (a->at(i)->canAttack(*turn)) {
            *ss <<" ";
        } else {
            *ss<<"*";
        }
        *ss<<"|";
        if (i != (int)a->size() -1) {
            printSpaces(spaceMeziMinionama,ss);
        }
    }
    printSpaces(windowScale/2 - totalSpace/2,ss);
    *ss<<"||"<<std::endl;


}

void GUI::drawMinionsStats(std::stringstream *ss, std::vector<Minion *> *a, int totalSpace, int spaceMeziMinionama) {
    int deficit = 0;
    if (a->at(0)->getAttack()>9)
        deficit++;

    printSpaces(windowScale/2 - totalSpace/2 - deficit,ss);

    for (int i = 0; i < (int)a->size(); i++) {
        int spaceDef = 0;
        *ss<<a->at(i)->getAttack()<<"/"<<a->at(i)->getHealth();

        if (a->at(i)->getAttack()>9)
            spaceDef++;
        if (a->at(i)->getHealth()>9)
            spaceDef++;

        if (i != (int)a->size() -1) {
            /*
            if (a->at(i+1)->getHealth()>9)
                spaceDef++;
            if (a->at(i+1)->getAttack()>9)
                spaceDef++;
            */
            printSpaces(spaceMeziMinionama - spaceDef,ss);
        }
    }
    int endDeficit = 0;
    if (a->at(a->size()-1)->getHealth()>9)
        endDeficit++;
    printSpaces(windowScale/2 - totalSpace/2 - endDeficit,ss);
    *ss<<"||"<<std::endl;
}

void GUI::drawMiddleLine(std::stringstream *ss) {
    for (int i = 0; i < windowScale; i++) {
        *ss << "-";
    }
    *ss<<std::endl;
}
