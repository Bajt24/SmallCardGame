#ifndef PA2_HEARTHSTONE_SPELL_H
#define PA2_HEARTHSTONE_SPELL_H

#include "Card.h"
/**
 * Spell is a card that holds an effect
 * It can be played only from hand
 */
class Spell : public Card{
public:
    virtual ~Spell()= default;
    /** Spell constructor */
    Spell(const std::string &name, int manaCost, int cardValue, Effect *effect)
            : Card(name, manaCost, cardValue, effect) {}

    Card *clone()const;
    std::string print()const;
    bool play(Board *b, Player *p, int /* turn */);
};


#endif //PA2_HEARTHSTONE_SPELL_H
