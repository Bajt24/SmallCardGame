#include <cstdlib>
#include <iostream>
#include "GameManager.h"
#include "../Entities/Player.h"

GameManager::GameManager() {
    pl1 = Player();
    pl2 = Player();
    board = Board(&currentPlayer,&pl1,&pl2);

}

Board * GameManager::getBoard(){
    return &board;
}

Player *GameManager::getCurrentPlayer(){
    if (currentPlayer == 0) {
        return &pl1;
    } else {
        return &pl2;
    }
}

Player *GameManager::getAnotherPlayer() {
    if (currentPlayer == 1) {
        return &pl1;
    } else {
        return &pl2;
    }
}

void GameManager::nextTurn() {
    Player * p = getAnotherPlayer();
    p->addUpRoundMana();
    p->drawCard();
    turn++;

    if (currentPlayer == 1) {
        currentPlayer = 0;
    } else {
        currentPlayer = 1;
    }
    if (ai != nullptr && ai->getP() == getCurrentPlayer()) {
        doAITurn();
        nextTurn();
    }
}

void GameManager::startGame(bool spawnAI) {
    cloneDecks();
    getCurrentPlayer()->drawCard();getCurrentPlayer()->drawCard();getCurrentPlayer()->drawCard();
    getAnotherPlayer()->drawCard();getAnotherPlayer()->drawCard();getAnotherPlayer()->drawCard();
    nextTurn();

    if (spawnAI)
        ai = new AIPlayer(&pl2);
}

void GameManager::cloneDecks() {
    //clones the selected cards
    for (int i = 0; i < (int)loader.getPl0Deck().size(); i++) {
        pl1.addCardToDeck(loader.getPl0Deck().at(i)->clone());
    }

    for (int i = 0; i < (int)loader.getPl1Deck().size(); i++) {
        pl2.addCardToDeck(loader.getPl1Deck().at(i)->clone());
    }
    srand(time(0));
    pl1.shuffleDeck();
    pl2.shuffleDeck();
}

int * GameManager::getTurn() {
    return &turn;
}

int GameManager::getCurrentPlayerIndex() const {
    return currentPlayer;
}

bool GameManager::playCard(int cardIndex) {
    if (finished)
        return false;
    Card * pt = getCurrentPlayer()->getHand()->at(cardIndex);
    if (!getCurrentPlayer()->getHand()->at(cardIndex)->play(&board,getCurrentPlayer(),turn))
        return false;
    getCurrentPlayer()->removeCard(pt);
    return true;
}

bool GameManager::playCard(Card*c) {
    if (finished)
        return false;
    if (!c->play(&board,getCurrentPlayer(),turn))
        return false;
    getCurrentPlayer()->removeCard(c);
    return true;
}


bool GameManager::load() {
    try {
        loader.load();
    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what();
        return false;
    }
    return true;
}

std::string GameManager::getCardsPath() {
    return loader.cardsPath;
}

int GameManager::getAnotherPlayerIndex() const {
    if (currentPlayer == 1) {
        return 0;
    } else {
        return 1;
    }
}

void GameManager::setCurrentPlayer(int currentPlayer) {
    GameManager::currentPlayer = currentPlayer;
}

void GameManager::setTurn(int turn) {
    GameManager::turn = turn;
}

AssetLoader * GameManager::getLoader() {
    return &loader;
}

void GameManager::setPl1(const Player &pl1) {
    GameManager::pl1 = pl1;
}

void GameManager::setPl2(const Player &pl2) {
    GameManager::pl2 = pl2;
}

void GameManager::setBoard(const Board &board) {
    GameManager::board = board;
}

GameManager &GameManager::operator=(const GameManager &g) {
    turn = g.turn;
    currentPlayer = g.currentPlayer;
    pl1 = g.pl1;
    pl2 = g.pl2;
    board = g.board;
    board.setCurrentPlayer(&currentPlayer);
    board.setPl1(&pl1);
    board.setPl2(&pl2);
    if (g.ai != nullptr)
        ai = new AIPlayer(&pl2);
    return *this;
}

void GameManager::doAITurn() {
    std::vector<Card*> cardsTBP = ai->playCards(&board);
    std::vector<Minion*> attacks = ai->doAttacks(&board,turn);

    for (int i = 0; i < (int)attacks.size(); i++) {
        bool playerWasKilled = false;
        board.attackTo((Entity*)(attacks.at(i)),(Entity*)(getAnotherPlayer()),turn,&playerWasKilled);
        if (playerWasKilled)
            finished = true;
    }
    for (int i = 0; i < (int)cardsTBP.size();i++) {
        playCard(cardsTBP.at(i));
    }

}

GameManager::~GameManager() {
    delete ai;
}

void GameManager::setGameFinished() {
    finished = true;
}

bool GameManager::isFinished() const {
    return finished;
}

void GameManager::setAI(Player *p) {
    ai = new AIPlayer(p);
}

AIPlayer *GameManager::getAi() const {
    return ai;
}

