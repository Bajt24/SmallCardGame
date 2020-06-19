#ifndef PA2_HEARTHSTONE_MINION_H
#define PA2_HEARTHSTONE_MINION_H

#include <climits>
#include "Card.h"
#include "../Entities/Entity.h"
/** The Minion class inherits from Card and Entity class
 *  It is the main element of our game. We can control it which means attacking to other minions or to the other player.
 * */
class Minion : public Card, public Entity{
public:
    virtual ~Minion();
    /** Constructor that contains no effect */
    Minion(const std::string &name, int manaCost, int cardValue, int attack, int health)
            : Card(name, manaCost, cardValue), Entity(attack,health) {};
    /** Constructor that contains an effect which is called whenever Minion enters board */
    Minion(const std::string &name, int manaCost, int cardValue, int attack, int health, Effect * effect)
            : Card(name, manaCost, cardValue, effect), Entity(attack,health) {};

    void setTurnPlayed(int turnPlayed) {
        Minion::turnPlayed = turnPlayed;
    }

    bool play(Board * b, Player * p, int turn);
    Card * clone()const;
    std::string print()const;
    bool canAttack(int turn)const;
private:
    int turnPlayed = INT_MAX;
};


#endif //PA2_HEARTHSTONE_MINION_H
