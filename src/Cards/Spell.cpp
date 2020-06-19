#include <sstream>
#include "Spell.h"
#include "../Entities/Player.h"

Card *Spell::clone() const{
    auto * m = new Spell(*this);
    Effect * newEffect = effect->clone();
    m->effect = newEffect;
    m->setCardPrefabIndex(this->cardPrefabIndex);
    return m;
}

std::string Spell::print() const{
    std::stringstream ss;
    ss << name << "[" << manaCost << "] : " << effect->print();
    return ss.str();
}

bool Spell::play(Board *b, Player *p, int /* turn */) {
    if (p->getMana() < manaCost)
        return false;

    effect->play(p,b);

    p->setMana(p->getMana() - manaCost);
    delete this;
    return true;
}

