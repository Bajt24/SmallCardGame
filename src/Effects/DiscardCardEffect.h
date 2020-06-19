#ifndef PA2_HEARTHSTONE_DISCARDCARDEFFECT_H
#define PA2_HEARTHSTONE_DISCARDCARDEFFECT_H


#include "Effect.h"
#include "../Entities/Player.h"
/**
 * It's a negative effect which discards random card(s) from your hand.
 */
class DiscardCardEffect : public Effect {
public:
    /** We can choose the damage done */
    DiscardCardEffect(int num) : cardsAmount(num) {};

    void play(Player * p, Board * /* b */);
    std::string print();
    Effect * clone();
private:
    int cardsAmount;
};


#endif //PA2_HEARTHSTONE_DISCARDCARDEFFECT_H
