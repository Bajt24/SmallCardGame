#ifndef PA2_HEARTHSTONE_GAINMANAEFFECT_H
#define PA2_HEARTHSTONE_GAINMANAEFFECT_H


#include "../Entities/Player.h"
/**
 * Positive effect which changes your maximum amount of mana crystals
 */
class GainManaEffect : public Effect{
public:
    /** We can choose the amount of mana crystals in constructor */
    GainManaEffect(int mana) : mana(mana){};

    void play(Player * p, Board * /* b */);
    std::string print();
    Effect * clone();
private:
    int mana;
};


#endif //PA2_HEARTHSTONE_GAINMANAEFFECT_H
