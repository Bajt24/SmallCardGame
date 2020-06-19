#ifndef PA2_HEARTHSTONE_CARD_H
#define PA2_HEARTHSTONE_CARD_H

#include <string>
#include "../Effects/Effect.h"

class Board;
class Player;
/**
 * The Card class is a superclass for Minions and Spells,
 * cards can be held in hand or in deck.
 */
class Card {
protected:
    std::string name;
    int manaCost, cardValue, cardPrefabIndex;
    Effect * effect = nullptr;
public:
    /** Constructor for card which contains no effect */
    Card(const std::string &name, int manaCost, int cardValue)
            : name(name), manaCost(manaCost),cardValue(cardValue) {};
    /** Constructor for card which contains an effect that is called when card is played */
    Card(const std::string &name, int manaCost, int cardValue, Effect * effect)
            : name(name), manaCost(manaCost),cardValue(cardValue),effect(effect) {};
    virtual ~Card();
    /** Makes a new deep copy of card */
    virtual Card * clone()const=0;
    /** Prints card info */
    virtual std::string print()const=0;
    /** Function that is called whenever you play this card */
    virtual bool play(Board * b, Player * p, int turn)=0;

    Effect *getEffect() const;
    const std::string &getName() const {
        return name;
    }
    int getManaCost() const {
        return manaCost;
    }
    int getCardValue() const {
        return cardValue;
    }
    int getCardPrefabIndex() const;
    void setCardPrefabIndex(int cardPrefabIndex);
};


#endif //PA2_HEARTHSTONE_CARD_H
