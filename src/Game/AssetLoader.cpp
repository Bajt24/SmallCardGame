#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "AssetLoader.h"
#include "../Cards/Minion.h"
#include "../Effects/DrawCardEffect.h"
#include "../Effects/DiscardCardEffect.h"
#include "../Cards/Spell.h"
#include "../Effects/DamageEnemyMinionsEffect.h"
#include "../Effects/HealHeroEffect.h"
#include "../Effects/GainManaEffect.h"

bool AssetLoader::load() {
    if (!loadCards()) {
        std::stringstream ss;
        ss << "There was an error with loading card presets.\nCheck file " << cardsPath << " for issues.";
        throw std::invalid_argument(ss.str());
    }
    if (!loadDecks()) {
        std::stringstream ss;
        ss << "There was an error with loading deck presets.\nCheck file " << decksPath << " for issues.";
        throw std::invalid_argument(ss.str());
    }
    if (!verifySelectedDecks()) {
        throw std::invalid_argument("There was an error with checking selected decks, make sure that they're in range.");
    }
    return true;
}

bool AssetLoader::loadCards() {
    std::ifstream o(cardsPath);
    std::string line;
    if (!o.is_open())
        return false;

    while (getline(o,line)) {
        if(o.fail() || o.bad())
            return false;
        std::istringstream ss(line);
        std::string token;

        if(line.substr(0, 2) == "//" || line == "") {
            continue;
        }

        std::vector<std::string> cardInfo;
        while(std::getline(ss, token, ';')) {
            cardInfo.push_back(token);
        }

        Card * card;
        if (!parseCard(cardInfo,&card))
            return false;
        card->setCardPrefabIndex((int)cards.size());
        cards.push_back(card);
    }
    return true;
}

const std::vector<Card*> &AssetLoader::getCards() const {
    return cards;
}

AssetLoader::~AssetLoader() {
    for (int i = 0; i < (int)cards.size(); i++) {
        delete cards[i];
    }

}

bool AssetLoader::parseCard(std::vector<std::string> arr, Card ** out) {
    Card * c = nullptr;
    try {
        if (arr[0]=="m") {
            if (!parseMinion(arr,&c))
                return false;
        } else if (arr[0]=="s") {
            if (!parseSpell(arr,&c))
                return false;
        } else {
            return false;
        }
    } catch (...) {
        return false;
    }
    if (c->getCardValue() < 0 || c->getManaCost() < 0 || c->getName() == "")
        return false;
    *out = c;
    return true;
}

bool AssetLoader::parseMinion(std::vector<std::string> arr, Card ** out) {
    Minion * m;
    Effect * e = nullptr;
    try {
        if (arr.size()==6) {
            m = new Minion(arr[1],strToInt(arr[2]),strToInt(arr[3]),strToInt(arr[4]),strToInt(arr[5]));
        } else if (arr.size() == 8) {
            if (!parseEffect(strToInt(arr[6]),strToInt(arr[7]),&e))
                return false;

            m = new Minion(arr[1],strToInt(arr[2]),strToInt(arr[3]),strToInt(arr[4]),strToInt(arr[5]),e);
        } else {
            return false;
        }
    } catch (...){
        if (e != nullptr)
            delete e;
        return false;
    }
    if (m->getHealth() < 1 || m->getAttack() < 0)
        return false;
    *out = (Card*)(m);
    return true;
}

bool AssetLoader::parseSpell(std::vector<std::string> arr, Card ** out) {
    Spell * m;
    Effect * e = nullptr;
    try {
        if (arr.size() == 6) {
            if (!parseEffect(strToInt(arr[4]),strToInt(arr[5]),&e))
                return false;

            m = new Spell(arr[1],strToInt(arr[2]),strToInt(arr[3]),e);
        } else {
            return false;
        }
    } catch (...){
        if (e != nullptr)
            delete e;
        return false;
    }
    *out = (Card*)(m);
    return true;
}

bool AssetLoader::parseEffect(int effect, int param, Effect ** out) {
    Effect * eff = nullptr;
    switch (effect) {
        case 0:
            eff = new DamageEnemyMinionsEffect(param);
            break;
        case 1:
            eff = new DiscardCardEffect(param);
            break;
        case 2:
            eff = new DrawCardEffect(param);
            break;
        case 3:
            eff = new GainManaEffect(param);
            break;
        case 4:
            eff = new HealHeroEffect(param);
            break;
        default:
            return false;
    }
    *out = eff;
    return true;
}

int AssetLoader::strToInt(std::string str) {
    char * e;
    int num = (int)std::strtol(str.c_str(),&e,10);
    if (*e != '\0')
        throw std::invalid_argument("Bad format");
    return num;
}

bool AssetLoader::loadDecks() {
    std::ifstream o(decksPath);
    std::string line;
    if (!o.is_open())
        return false;
    while (getline(o,line)) {
        if(o.fail() || o.bad())
            return false;
        std::istringstream ss(line); std::string token;
        if(line.substr(0, 2) == "//" || line == "")
            continue;

        std::vector<std::string> cardInfo;
        while(std::getline(ss, token, ';')) {
            cardInfo.push_back(token);
        }
        if (!parseDeck(&cardInfo))
            return false;
    }
    return true;
}


bool AssetLoader::parseDeck(std::vector<std::string> * info) {
    if (info->size() < 1)
        return false;
    std::vector<Card*> deck;
    try {
        if (info->at(0).substr(0, 3) == "pl0") {
            pl0selDeck = strToInt(info->at(1)); return true;
        }

        if (info->at(0).substr(0, 3) == "pl1") {
            pl1selDeck = strToInt(info->at(1)); return true;
        }

        for (int i = 0; i < (int)info->size();i++) {
            int cardIndex = strToInt(info->at(i));
            if (cardIndex >= 0 && cardIndex < (int)cards.size()) {
                deck.push_back(cards.at(cardIndex));
            } else {
                return false;
            }
        }
    } catch (...) {
        return false;
    }
    decks.push_back(deck);
    return true;
}

bool AssetLoader::verifySelectedDecks() const{
    return (pl0selDeck >= 0 && pl0selDeck < (int)decks.size() && pl1selDeck >= 0 && pl1selDeck < (int)decks.size());
}

const std::vector<Card *> AssetLoader::getPl1Deck() {
    return decks.at(pl1selDeck);
}

const std::vector<Card *> AssetLoader::getPl0Deck() {
    return decks.at(pl0selDeck);
}




