#include <algorithm>
#include <iostream>
#include "Board.h"

bool Board::placeMinion(Minion * m) {
    std::vector<Minion*> *pt = getCurrentBoard();

    if (pt->size()>boardSize-1)
        return false;

    pt->push_back(m);
    return true;
}

void Board::setCurrentPlayer(int *currentPlayer) {
    Board::currentPlayer = currentPlayer;
}

bool Board::removeMinion(Minion * m) {
    std::vector<Minion*> *pt = getCurrentBoard();
    //hledame v obou boardech
    for (int i = 0; i < (int)pt->size(); i++) {
        Minion * a = pt->at(i);

        if (a == m) {
            pt->erase(pt->begin()+i);
            delete m;
            return true;
        }
    }

    pt = getAnotherBoard();
    for (int i = 0; i < (int)pt->size(); i++) {
        Minion * a = pt->at(i);

        if (a == m) {
            pt->erase(pt->begin()+i);
            delete m;
            return true;
        }
    }

    return false;
}

std::vector<Minion*> *Board::getCurrentBoard() {
    std::vector<Minion*> *pt;
    if (*currentPlayer == 0) {
        pt = &board1;
    } else {
        pt = &board2;
    }
    return pt;
}

std::vector<Entity*> Board::availableTargets(){
    std::vector<Entity*> entities;
    std::vector<Minion*> * board = getAnotherBoard();
    for (int i = 0; i < (int)board->size(); i++) {
        entities.push_back(board->at(i));
    }
    entities.push_back(getAnotherPlayer());
    return entities;
}

std::vector<Minion*> * Board::getAnotherBoard() {
    std::vector<Minion*> *pt;
    if (*currentPlayer == 1) {
        pt = &board1;
    } else {
        pt = &board2;
    }
    return pt;
}

Entity * Board::getAnotherPlayer() const{
    if (*currentPlayer == 0) {
        return pl2;
    } else {
        return pl1;
    }
}

bool Board::attackTo(Entity *from, Entity *to, int turn, bool * playerWasKilled) {
    if (!from->canAttack(turn))
        return false;
    return (singleAttack(from,to, turn, playerWasKilled) && singleAttack(to,from, turn, playerWasKilled));
}

Board::Board(int * currentPlayer, Entity *pl1, Entity *pl2) : currentPlayer(currentPlayer),pl1(pl1), pl2(pl2) {}

std::vector<Minion *> Board::availableAttackers(int turn) {
    std::vector<Minion *> attackers;
    std::vector<Minion*> * b = getCurrentBoard();
    for (int i = 0; i < (int)getCurrentBoard()->size(); i++) {
        Minion * m = b->at(i);
        if (m->canAttack(turn))
            attackers.push_back(m);
    }
    return attackers;
}

bool Board::singleAttack(Entity *from, Entity *to, int turn, bool * playerWasKilled) {
    bool isKilled = false;
    to->damage(from->getAttack(),&isKilled);
    from->setLastAttackedTurn(turn);
    if (isKilled) {
        if (typeid(*to) == typeid(Minion)) {
            removeMinion((Minion*)(to));
        } else {
            if (playerWasKilled != nullptr)
                *playerWasKilled = true;
        }
    }
    return true;
}

Board::~Board() {
    for (int i = 0; i < (int)board1.size(); i++) {
        delete board1.at(i);
    }
    for (int i = 0; i < (int)board2.size(); i++) {
        delete board2.at(i);
    }
}

void Board::setBoard(std::vector<Minion *> board, int playerIndex) {
    if (playerIndex == 0) {
        board1 = board;
    } else {
        board2 = board;
    }
}

Board &Board::operator=(const Board &b) {
    this->currentPlayer = b.currentPlayer;
    this->pl1 = b.pl1;
    this->pl2 = b.pl2;
    //zklonujeme boardy
    for (int i = 0; i < (int)b.board1.size(); i++) {
        Card * c = b.board1.at(i)->clone();
        board1.push_back((Minion*)(c));
    }
    for (int i = 0; i < (int)b.board2.size(); i++) {
        Card * c = b.board2.at(i)->clone();
        board2.push_back((Minion*)(c));
    }
    return *this;
}

void Board::setPl1(Entity *pl1) {
    Board::pl1 = pl1;
}

void Board::setPl2(Entity *pl2) {
    Board::pl2 = pl2;
}

