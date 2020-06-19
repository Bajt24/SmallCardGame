#include "Entity.h"


void Entity::damage(int dmg, bool * isKilled) {
    health -= dmg;
    if (health < 1)
        *isKilled = true;
}

Entity::Entity(int attack, int health) : attack(attack), health(health) {
    maxHealth = health;
}

int Entity::getAttack() const {
    return attack;
}

int Entity::getHealth() const {
    return health;
}

int Entity::getMaxHealth() const {
    return maxHealth;
}

void Entity::heal(int amount) {
    health += amount;
    if (health > maxHealth)
        health = maxHealth;
}

int Entity::getLastAttackedTurn() const {
    return lastAttackedTurn;
}

void Entity::setMaxHealth(int maxHealth) {
    Entity::maxHealth = maxHealth;
}

void Entity::setAttack(int attack) {
    Entity::attack = attack;
}

void Entity::setHealth(int health) {
    Entity::health = health;
}

void Entity::setLastAttackedTurn(int lastAttackedTurn) {
    Entity::lastAttackedTurn = lastAttackedTurn;
}
