#include <sstream>
#include "DrawCardEffect.h"


void DrawCardEffect::play(Player *p, Board * /* *b */) {
    for (int i = 0; i < cards; i++) {
        p->drawCard();
    }
}

std::string DrawCardEffect::print() {
    std::stringstream ss;
    if (cards == 1)
        return "Draw 1 card";
    ss << "Draw " << cards << " cards";
    return ss.str();
}

Effect *DrawCardEffect::clone() {
    return new DrawCardEffect(cards);
}
