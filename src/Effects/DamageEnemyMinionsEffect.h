#ifndef PA2_HEARTHSTONE_DAMAGEENEMYMINIONSEFFECT_H
#define PA2_HEARTHSTONE_DAMAGEENEMYMINIONSEFFECT_H


#include "../Entities/Player.h"
/**
 * Effect that does damage to enemy minions on board
 */
class DamageEnemyMinionsEffect : public Effect{
public:
    /** We can choose the damage done to minions in constructor */
    DamageEnemyMinionsEffect(int dmg) : dmg(dmg){};

    void play(Player * /* p */, Board * b);
    std::string print();
    Effect * clone();
private:
    int dmg;
};


#endif //PA2_HEARTHSTONE_DAMAGEENEMYMINIONSEFFECT_H
