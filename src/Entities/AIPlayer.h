#ifndef PA2_HEARTHSTONE_AIPLAYER_H
#define PA2_HEARTHSTONE_AIPLAYER_H


#include "Player.h"
/**
 * Class that controls player with AI
 */

class AIPlayer{
public:
    AIPlayer(Player * p) : p(p) {};
    std::vector<Minion*> doAttacks(Board * b, int turn);
    std::vector<Card*> playCards(Board * b);

    Player * getP();
private:
    Player * p;
};


#endif //PA2_HEARTHSTONE_AIPLAYER_H
