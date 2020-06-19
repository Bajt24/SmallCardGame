#include "Card.h"


Card::~Card() {
    delete effect;
}

int Card::getCardPrefabIndex() const {
    return cardPrefabIndex;
}

void Card::setCardPrefabIndex(int cardPrefabIndex) {
    Card::cardPrefabIndex = cardPrefabIndex;
}

Effect *Card::getEffect() const {
    return effect;
}
