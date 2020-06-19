#include <sstream>
#include "HealHeroEffect.h"

void HealHeroEffect::play(Player *p, Board * /* b */) {
    p->heal(healAmount);
}

std::string HealHeroEffect::print() {
    std::stringstream ss;
    ss << "Heal hero for " << healAmount << "HP";
    return ss.str();
}

Effect *HealHeroEffect::clone() {
    return new HealHeroEffect(healAmount);
}
