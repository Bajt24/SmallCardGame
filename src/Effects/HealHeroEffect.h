#ifndef PA2_HEARTHSTONE_HEALHEROEFFECT_H
#define PA2_HEARTHSTONE_HEALHEROEFFECT_H


#include <string>
#include "../Entities/Player.h"
/**
 * Effect that heals our player
 */
class HealHeroEffect : public Effect {
public:
    /** We can choose the HP healed in constructor.*/
    HealHeroEffect(int num) : healAmount(num) {};
    void play(Player * p, Board * /* b */);
    std::string print();
    Effect * clone();
private:
    int healAmount;
};


#endif //PA2_HEARTHSTONE_HEALHEROEFFECT_H
