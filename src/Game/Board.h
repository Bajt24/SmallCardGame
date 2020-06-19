#ifndef PA2_HEARTHSTONE_BOARD_H
#define PA2_HEARTHSTONE_BOARD_H


#include <vector>
#include <memory>
#include <list>
#include <climits>
#include "../Cards/Minion.h"
#include "../Entities/Player.h"
/**
 * Class that handles board and minions on board
 * It also takes care of their interaction
 */
class Board {
private:
public:
    Board()=default;
    Board(int * currentPlayer, Entity *pl1, Entity *pl2);

    virtual ~Board();
    static const int boardSize = 7;
    /** Copy constructor */
    Board & operator=(const Board & b);
    /** Places minion on board*/
    bool placeMinion(Minion * m);
    /** Removes minion from board*/
    bool removeMinion(Minion * m);
    /** Function that deals with attacking of entities to other entities */
    bool attackTo(Entity * from,Entity * to, int turn, bool * playerWasKilled = nullptr);

    std::vector<Minion*> * getCurrentBoard();
    std::vector<Minion*> * getAnotherBoard();
    /** Returns available attackers */
    std::vector<Minion *> availableAttackers(int turn = INT_MAX);
    /** Returns available targets */
    std::vector<Entity*> availableTargets();

    void setBoard(std::vector<Minion *> board, int playerIndex);
    void setPl1(Entity *pl1);
    void setPl2(Entity *pl2);
    void setCurrentPlayer(int *currentPlayer);
private:
    int * currentPlayer;
    std::vector<Minion*> board1,board2;
    Entity * pl1,*pl2;
    Entity * getAnotherPlayer()const;
    /** Function that does one-sided attack */
    bool singleAttack(Entity * from, Entity * to, int turn, bool * playerWasKilled = nullptr);
};

#endif //PA2_HEARTHSTONE_BOARD_H