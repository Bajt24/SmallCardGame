#include <iostream>
#include <algorithm>
#include "AIPlayer.h"

std::vector<Minion*> AIPlayer::doAttacks(Board *b, int turn) {
    std::vector<Minion*> aa;
    std::vector<Minion*> * m = b->getCurrentBoard();
    //we will only picks those minions that can attack this turn
    for (int i = 0; i < (int)m->size(); i++) {
        if (m->at(i)->canAttack(turn))
            aa.push_back(m->at(i));
    }
    return aa;
}

std::vector<Card *> AIPlayer::playCards(Board *b) {
    std::vector<Card*> cardsToBePlayed;
    std::vector<Card*> playableCards = p->getPlayableHand(p->getMana());
    int cardLimit = b->boardSize - (int)b->getCurrentBoard()->size();

    if ((int)playableCards.size() < cardLimit)
        cardLimit = (int)playableCards.size();

    std::sort(playableCards.begin(),playableCards.end(),[](Card * a,Card * b){
       return a->getManaCost() > b->getManaCost();
    });

    int mana = p->getMana();
    for (int i = 0; i < cardLimit; i++) {
        Card * c = playableCards.at(i);
        if (mana - c->getManaCost() >= 0) {
            cardsToBePlayed.push_back(c);
            mana-=c->getManaCost();
        }
        if (mana == 0)
            break;
    }

    return cardsToBePlayed;
}

Player *AIPlayer::getP() {
    return p;
}
