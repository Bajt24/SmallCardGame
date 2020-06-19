#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include "GameSaver.h"
#include "../Cards/Spell.h"

bool GameSaver::saveGame(std::string name, GameManager *g) {
    std::ofstream o(name);
    if (!o.is_open())
        return false;
    mapa.clear();
    try {
        if (!dumpCardsModified(g->getCardsPath()))
            return false;
        dumpGameManager(g);
        dumpPlayer(g->getCurrentPlayer(),g->getCurrentPlayerIndex(),g->getBoard()->getCurrentBoard());
        dumpPlayer(g->getAnotherPlayer(),g->getAnotherPlayerIndex(),g->getBoard()->getAnotherBoard());

        for (auto it = mapa.begin(); it != mapa.end(); it++)
        {
            o << it.operator*().first << ";" << it.operator*().second << std::endl;
            if(o.fail() || o.bad())
                return false;
        }
        o.close();
        return ((bool)o);
    } catch (...) {
        return false;
    }
}

void GameSaver::dumpPlayer(Player * p, int playerIndex, const std::vector<Minion*>* m) {
    std::stringstream ss;
    ss << p->getAttack() << ";" << p->getHealth() << ";" << p->getMaxHealth() << ";"  << p->getMana() << ";" << p->getMaxMana() << ";" << p->getHand()->size() << ";" << p->getDeck()->size() << ";" << m->size();
    mapa.insert({"pl" + std::to_string(playerIndex),ss.str()});

    dumpPlayerHand(p, playerIndex);
    dumpPlayersBoard(m,playerIndex);
    dumpPlayersDeck(p,playerIndex);
}


bool GameSaver::dumpCardsModified(std::string path) {
    long long time;
    if (!getCardsModifiedDate(path, &time))
        return false;

    mapa.insert({std::string("cardsModified"),std::to_string(time)});
    return true;
}

void GameSaver::dumpPlayerHand(Player * p, int playerIndex) {
    for (int i = 0; i < (int)p->getHand()->size(); i++) {
        Card * pt = p->getHand()->at(i);
        mapa.insert({"pl" + std::to_string(playerIndex) + "hand" + std::to_string(i),std::to_string(pt->getCardPrefabIndex())});
    }
}

void GameSaver::dumpPlayersDeck(Player * p, int playerIndex) {
    for (int i = 0; i < (int)p->getDeck()->size(); i++) {
        Card * pt = p->getDeck()->at(i);
        mapa.insert({"pl" + std::to_string(playerIndex) + "deck" + std::to_string(i),std::to_string(pt->getCardPrefabIndex())});
    }
}

void GameSaver::dumpPlayersBoard(const std::vector<Minion*> * b, int playerIndex) {
    for (int i = 0; i < (int)b->size(); i++) {
        Minion * pt = b->at(i);
        std::stringstream ss;
        ss  << pt->getCardPrefabIndex() << ";" << pt->getAttack() << ";" << pt->getHealth() << ";" << pt->getLastAttackedTurn();
        mapa.insert({"pl" + std::to_string(playerIndex) + "board" + std::to_string(i),ss.str()});
    }
}

void GameSaver::dumpGameManager(GameManager * g) {
    mapa.insert({"currentPlayer",std::to_string(g->getCurrentPlayerIndex())});
    mapa.insert({"turn",std::to_string(*g->getTurn())});
    if (g->getAi() != nullptr)
        mapa.insert({"ai","true"});
}

bool GameSaver::loadGame(std::string name, GameManager ** g) {
    if (!parseLines(name))
        return false;
    try {
        GameManager g2 = GameManager();
        if (!g2.load())
            return false;
        Player p1,p2;
        Board b(g2.getTurn(),&p1,&p2);
        if (!(loadGameManager(&g2)
            && loadPlayer(0,&p1,&b,&g2.getLoader()->getCards())
            && loadPlayer(1,&p2,&b,&g2.getLoader()->getCards())))
                return false;
        g2.setBoard(b);
        g2.setPl1(p1);
        g2.setPl2(p2);
        if (aiFlag)
            g2.setAI(&p2);
        **g = g2;

    } catch (...) {
        return false;
    }
    return true;
}

bool GameSaver::parseLines(std::string name) {
    std::ifstream o(name);
    std::string line;
    if (!o.is_open())
        return false;

    mapa.clear();
    while (getline(o,line)) {
        if(o.fail() || o.bad())
            return false;
        std::istringstream ss(line);
        std::string token;
        //skip empty rows and commented rows
        if(line.substr(0, 2) == "//" || line == "") {
            continue;
        }
        //parseneme string do mapy
        std::string key, value;
        std::getline(ss, key, ';');
        std::getline(ss, value);

        mapa.insert({key,value});
    }
    return true;
}

bool GameSaver::loadGameManager(GameManager *g) {
    //check if cards were modified
    if (mContains("cardsModified")) {
        long long time;
        if (!getCardsModifiedDate(g->getCardsPath(),&time))
            return false;
        if (time != std::stoll(mapa.find("cardsModified").operator*().second,nullptr,10))
            return false;
    }
    std::vector<std::string> keys = {"turn","currentPlayer"};
    if (!mContains(keys))
        return false;
    if (mContains("ai"))
        aiFlag = true;

    g->setCurrentPlayer(std::stoi(get("currentPlayer"),nullptr,10));
    g->setTurn(std::stoi(get("turn"),nullptr,10));
    return true;
}

bool GameSaver::getCardsModifiedDate(std::string path, long long *out) {
    struct stat st;
    if (stat(path.c_str(), &st)) {
        return false;
    } else {
        *out = (long long)st.st_mtim.tv_sec;
        return true;
    }
}

bool GameSaver::mContains(std::string key) {
    return mapa.find(key) != mapa.end();
}

bool GameSaver::mContains(std::vector<std::string> keys) {
    for (int i = 0; i < (int)keys.size();i++) {
        if (mapa.find(keys.at(i)) == mapa.end())
            return false;
    }
    return true;
}

std::string GameSaver::get(std::string key) {
    return mapa.find(key).operator*().second;
}

bool GameSaver::loadPlayer(int playerIndex, Player *p, Board * b, const std::vector<Card*> * prefabs) {
    std::vector<std::string> pl = parseStr(get("pl"+std::to_string(playerIndex)));
    try {
        *p = Player(AssetLoader::strToInt(pl[0]),AssetLoader::strToInt(pl[1]));
        p->setMaxHealth(AssetLoader::strToInt(pl[2]));
        p->setMana(AssetLoader::strToInt(pl[3]));
        p->setMaxMana(AssetLoader::strToInt(pl[4]));

        std::vector<Card*> hand, deck; std::vector<Minion*> board;

        if (!(loadPlayersHand(playerIndex,AssetLoader::strToInt(pl[5]),&hand,prefabs)
            && loadPlayersDeck(playerIndex,AssetLoader::strToInt(pl[6]),&deck,prefabs)
            && loadPlayersBoard(playerIndex,AssetLoader::strToInt(pl[7]),&board,prefabs)))
            return false;
        p->setHand(hand); p->setDeck(deck);
        b->setBoard(board,playerIndex);
    } catch (...) {
        return false;
    }
    return true;
}

std::vector<std::string> GameSaver::parseStr(std::string str) {
    std::istringstream ss(str);
    std::string token;

    std::vector<std::string> arr;
    while(std::getline(ss, token, ';')) {
        arr.push_back(token);
    }
    return arr;
}

bool GameSaver::loadPlayersHand(int playerIndex, int handsize, std::vector<Card *> * hand, const std::vector<Card*> * prefabs) {
    for (int i = 0; i < handsize; i++) {
        std::string s = "pl"+std::to_string(playerIndex)+"hand"+std::to_string(i);
        if (!mContains(s))
            return false;
        int prefabIndex = AssetLoader::strToInt(get(s));
        hand->push_back(prefabs->at(prefabIndex)->clone());
    }
    return true;
}

bool GameSaver::loadPlayersDeck(int playerIndex, int decksize, std::vector<Card *> *deck, const std::vector<Card *> *prefabs) {
    for (int i = 0; i < decksize; i++) {
        std::string s = "pl"+std::to_string(playerIndex)+"deck"+std::to_string(i);
        if (!mContains(s))
            return false;
        int prefabIndex = AssetLoader::strToInt(get(s));
        deck->push_back(prefabs->at(prefabIndex)->clone());
    }
    return true;
}

bool GameSaver::loadPlayersBoard(int playerIndex, int boardsize, std::vector<Minion *> * board, const std::vector<Card *> *prefabs) {
    for (int i = 0; i < boardsize; i++) {
        std::string s = "pl"+std::to_string(playerIndex)+"board"+std::to_string(i);
        if (!mContains(s))
            return false;

        std::vector<std::string> arr = parseStr(get(s));

        int prefabIndex = AssetLoader::strToInt(arr[0]);
        Card * card = prefabs->at(prefabIndex)->clone();
        Minion * m = (Minion*)(card);
        //we have cloned the card from presets but we still have to set the current state stats
        m->setAttack(AssetLoader::strToInt(arr[1]));
        m->setHealth(AssetLoader::strToInt(arr[2]));
        m->setLastAttackedTurn(AssetLoader::strToInt(arr[3]));
        m->setTurnPlayed(0);
        board->push_back(m);
    }
    return true;
}