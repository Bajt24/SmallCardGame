#include "DiscardCardEffect.h"
#include <sstream>

void DiscardCardEffect::play(Player *p, Board * /* b */) {
    if (cardsAmount >= (int)p->getHand()->size()) {
        p->discardHand(this);
        return;
    }
    for (int i = 0; i < cardsAmount; i++) {
        p->discardCard(this);
    }
}

std::string DiscardCardEffect::print() {
    std::stringstream ss;
    if (cardsAmount == 1)
        return "Discard 1 card";

    ss << "Discard " << cardsAmount << " cards";
    return ss.str();
}

Effect *DiscardCardEffect::clone() {
    return new DiscardCardEffect(cardsAmount);
}
