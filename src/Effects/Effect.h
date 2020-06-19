#ifndef PA2_HEARTHSTONE_EFFECT_H
#define PA2_HEARTHSTONE_EFFECT_H

#include <string>

class Player; class Board;
/**
 * Can be stored in cards and is called whenever the card is played
 * It can be a negative or a positive one and affects players or board in some way
 */
class Effect {
public:
    Effect()= default;

    virtual ~Effect()=default;
    /** Makes a new deep copy of an effect */
    virtual Effect * clone()=0;
    /** Prints effect info */
    virtual std::string print()=0;
    /** Function that is called whenever you play this effect */
    virtual void play(Player * p, Board * b)=0;
};


#endif //PA2_HEARTHSTONE_EFFECT_H
