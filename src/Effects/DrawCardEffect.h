#ifndef PA2_HEARTHSTONE_DRAWCARDEFFECT_H
#define PA2_HEARTHSTONE_DRAWCARDEFFECT_H


#include "../Entities/Player.h"
/**
 * Effect that draws specific amount of cards to your hand
 */
class DrawCardEffect : public Effect {
public:
    /** We can choose the amount of cards drawn in constructor */
    DrawCardEffect(int num) : cards(num) {};

    void play(Player * p, Board * /* b */);
    std::string print();
    Effect * clone();
private:
    int cards;
};


#endif //PA2_HEARTHSTONE_DRAWCARDEFFECT_H
