#ifndef PA2_HEARTHSTONE_ENTITY_H
#define PA2_HEARTHSTONE_ENTITY_H

#include <string>
#include <climits>
/**
 * Class that wraps everything that is "alive".
 * That means everything that has health and attack.
 */
class Entity {
protected:
    int attack, health, maxHealth, lastAttackedTurn = INT_MAX;
public:
    Entity()= default;
    /** Constructor that sets the health and attack values */
    Entity(int attack, int health);
    virtual ~Entity() {};
    /** Pure virtual function that check if entity can attack */
    virtual bool canAttack(int turn)const=0;
    /** Pure virtual function that provides print of entity */
    virtual std::string print()const=0;
    /** Heals entity */
    void heal(int health);
    /** Does damage to our entity. It also has an output parameter containing info if our entity was killed */
    void damage(int dmg, bool* isKilled);

    void setAttack(int attack);
    void setHealth(int health);
    void setLastAttackedTurn(int lastAttackedTurn);
    void setMaxHealth(int maxHealth);

    int getAttack() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getLastAttackedTurn() const;

};
#endif //PA2_HEARTHSTONE_ENTITY_H