#ifndef PA2_HEARTHSTONE_PLAYER_H
#define PA2_HEARTHSTONE_PLAYER_H


#include <vector>
#include "Entity.h"
#include "../Cards/Card.h"
#include "../Game/Board.h"
#include "../Effects/DiscardCardEffect.h"

class DiscardCardEffect;

/**
 * One of the key classes is Player. His main object is to survive. There can be only two players ingame.
 * Player holds card in his hand the rest of them is shuffled in his deck.
 */
class Player : public Entity{
private:
    std::vector<Card*> hand, deck;
    int mana = 0, maxMana = 0;
public:
    static const int manaTopLimit = 10;
    static const int handSize = 10;
    static const int startingPlayerHP = 30;

    /** Constructor that sets attack and health of player */
    Player(int attack, int health);
    Player();
    virtual ~Player();
    /** Copy constructor */
    Player & operator=(const Player & p);
    /** Suffles card into deck */
    void addCardToDeck(Card * card);
    /** Draws a card from deck puts it into hand */
    bool drawCard();
    /** Discards a card from hand */
    void discardCard(DiscardCardEffect * ignoredOne);
    /** Function that is called whenever we want to discard whole hand */
    void discardHand(DiscardCardEffect * ignoredOne);
    /** Removes (destroys) card from hand */
    void removeCard(Card * pt);
    /** Function that adds up the maximum mana amount and resets the used mana at the round end */
    bool addUpRoundMana();
    /** Shuffles the deck */
    void shuffleDeck();
    /** It gets collection of playable cards in your hand */
    std::vector<Card*> getPlayableHand(int mana);

    void setHand(const std::vector<Card *> &hand);
    void setMana(int mana);
    void setMaxMana(int maxMana);
    void setDeck(const std::vector<Card *> &deck);

    int getMana() const;
    const std::vector<Card *> * getHand() const;
    const std::vector<Card *> * getDeck() const;
    std::string print() const;
    bool canAttack(int /* turn */) const;
    int getMaxMana() const;

};


#endif //PA2_HEARTHSTONE_PLAYER_H
