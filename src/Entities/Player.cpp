#include <random>
#include <algorithm>
#include "Player.h"
#include "../Effects/DiscardCardEffect.h"
#include <sstream>

Player::Player(int attack, int health) : Entity(attack, health) {}

void Player::addCardToDeck(Card * card) {
    deck.push_back(card);
}

bool Player::drawCard() {
    if (deck.empty() || hand.size()==handSize)
        return false;

    hand.push_back(deck.at(deck.size()-1));
    deck.pop_back();

    return true;
}

void Player::shuffleDeck() {
    std::random_shuffle(std::begin(deck), std::end(deck));
}

Player::Player() {
    health = startingPlayerHP;
    maxHealth = health;
    attack = 0;
}

Player::~Player() {
    for (int i = 0; i<(int)deck.size(); i++) {
        delete deck[i];
    }
    for (int i = 0; i<(int)hand.size(); i++) {
        delete hand[i];
    }
}

const std::vector<Card *> * Player::getHand() const {
    return &hand;
}

const std::vector<Card *> * Player::getDeck() const {
    return &deck;
}

int Player::getMana() const {
    return mana;
}

void Player::setMana(int mana) {
    this->mana = mana;
}

int Player::getMaxMana() const {
    return maxMana;
}

void Player::setMaxMana(int maxMana) {
    this->maxMana = maxMana;
}


bool Player::addUpRoundMana() {
    if (maxMana >= manaTopLimit)
        return false;

    maxMana++;
    mana = maxMana;

    return true;
}

std::string Player::print() const{
    std::stringstream s;
    s << "Player " << getHealth() << "HP";
    return s.str();
}


void Player::removeCard(Card * pt) {
    for (int i = 0; i < (int)hand.size(); i++) {
        if (hand.at(i) == pt) {
            hand.erase(hand.begin()+i);
            break;
        }
    }
}

bool Player::canAttack(int /* turn */) const {
    return false;
}

void Player::discardCard(DiscardCardEffect * ignoredOne) {
    if (hand.size() != 0 && hand.size() != 1) {
        int output = 0 + (rand() % static_cast<int>(hand.size()));
        Card * pt = hand.at(output);
        if (pt->getEffect() == ignoredOne) {
            return discardCard(ignoredOne);
        }
        removeCard(pt);
        delete pt;
    }
}

void Player::discardHand(DiscardCardEffect *ignoredOne) {
    for (auto it = hand.begin(); it != hand.end(); ) {
        if (it.operator*()->getEffect() != ignoredOne) {
            Card * pt = it.operator*();
            it = hand.erase(it);
            delete pt;
        } else {
            ++it;
        }
    }
}

void Player::setHand(const std::vector<Card *> &hand) {
    Player::hand = hand;
}

void Player::setDeck(const std::vector<Card *> &deck) {
    Player::deck = deck;
}

Player &Player::operator=(const Player &p) {
    this->mana = p.mana;
    this->maxMana = p.maxMana;
    this->health = p.health;
    this->maxHealth = p.maxHealth;
    this->lastAttackedTurn = p.lastAttackedTurn;
    this->attack = p.attack;
    //clone deck and hand
    for (int i = 0; i < (int)p.getHand()->size(); i++) {
        Card * c = p.getHand()->at(i)->clone();
        hand.push_back(c);
    }
    for (int i = 0; i < (int)p.getDeck()->size(); i++) {
        Card * c = p.getDeck()->at(i)->clone();
        deck.push_back(c);
    }
    return *this;
}

std::vector<Card *> Player::getPlayableHand(int mana) {
    std::vector<Card *> playableCards;
    for (int i = 0; i < (int)hand.size(); i++) {
        if (hand.at(i)->getManaCost() <= mana)
            playableCards.push_back(hand.at(i));
    }
    return playableCards;
}




