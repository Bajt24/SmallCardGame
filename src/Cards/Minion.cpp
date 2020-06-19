#include <sstream>
#include "Minion.h"
#include "../Game/GameManager.h"

Card * Minion::clone() const {

    auto * m = new Minion(*this);
    if (effect != nullptr) {
        Effect * newEffect = effect->clone();
        m->effect = newEffect;
    }
    m->setCardPrefabIndex(this->cardPrefabIndex);
    return m;
}

bool Minion::canAttack(int turn) const{
    return (turn > turnPlayed && turn > lastAttackedTurn);
}

Minion::~Minion() {}

std::string Minion::print() const{
    std::stringstream s;
    s << getAttack()<<"/"<<getHealth() << " [" << getManaCost() << "] " << getName();
    if (effect != nullptr)
        s << " (" << effect->print() << ")";
    return s.str();
}

bool Minion::play(Board *b, Player *p, int turn) {
    //check if we even have enough mana
    if (p->getMana() < manaCost)
        return false;
    //try to place it onto board
    if (!b->placeMinion(this))
        return false;

    p->setMana(p->getMana() - manaCost);
    //execute an effect if we have any
    if (effect!= nullptr)
        effect->play(p,b);
    this->setTurnPlayed(turn);
    this->setLastAttackedTurn(turn);
    return true;
}