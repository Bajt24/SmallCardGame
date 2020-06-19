#include <sstream>
#include "GainManaEffect.h"

void GainManaEffect::play(Player *p, Board * /* b */) {
    int finalMana = mana + p->getMaxMana();
    if (finalMana > p->manaTopLimit)
        finalMana = p->manaTopLimit;
    p->setMaxMana(finalMana);
}

std::string GainManaEffect::print() {
    std::stringstream ss;
    ss << "Gain " << mana << " mana";
    return ss.str();
}

Effect *GainManaEffect::clone() {
    return new GainManaEffect(mana);
}
