#include <sstream>
#include "DamageEnemyMinionsEffect.h"

void DamageEnemyMinionsEffect::play(Player * /* p */, Board *b) {
    std::vector<Minion *> * minions = b->getAnotherBoard();
    std::vector<Minion *> mini = *minions;
    for (int i = 0; i < (int)minions->size(); i++) {

        Minion * m = minions->at(i);
        bool isKilled = false;
        m->damage(dmg,&isKilled);
        if (isKilled)
            b->removeMinion(m);
    }
}

std::string DamageEnemyMinionsEffect::print() {
    std::stringstream ss;
    ss << "Deal " << dmg << " damage to enemy minions";
    return ss.str();
}

Effect *DamageEnemyMinionsEffect::clone() {
    return new DamageEnemyMinionsEffect(dmg);
}
