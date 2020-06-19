#ifndef PA2_HEARTHSTONE_GAMEMANAGER_H
#define PA2_HEARTHSTONE_GAMEMANAGER_H

#include "AssetLoader.h"
#include "../Entities/Player.h"
#include "Board.h"
#include "../Entities/AIPlayer.h"

/**
 * Class that wraps the current game state a takes care of correct run
 */
class GameManager {
public:
    GameManager();

    virtual ~GameManager();

    /** Handles starting of a new game*/
    void startGame(bool spawnAI = false);
    /** Ends the current round and starts the next one*/
    void nextTurn();
    /** Loads all the required assets required to run the game*/
    bool load();
    /** Copy constructor */
    GameManager & operator=(const GameManager & g);
    /** Takes care of playing the selected card*/
    bool playCard(int cardIndex);
    /** Takes care of playing the selected card*/
    bool playCard(Card * c);
    /** Clones the loaded cards and puts them into players' decks*/
    void cloneDecks();

    int getAnotherPlayerIndex() const;
    int getCurrentPlayerIndex() const;
    bool isFinished() const;
    AssetLoader * getLoader();
    int * getTurn();
    Player * getCurrentPlayer();
    Player * getAnotherPlayer();
    Board * getBoard();
    std::string getCardsPath();

    void setAI(Player * p);

    AIPlayer *getAi() const;

    void setGameFinished();
    void setCurrentPlayer(int currentPlayer);
    void setPl1(const Player &pl1);
    void setPl2(const Player &pl2);
    void setBoard(const Board &board);
    void setTurn(int turn);
private:
    /** Makes an AI turn */
    void doAITurn();

    bool finished = false;
    AssetLoader loader;
    Player pl1,pl2;
    AIPlayer * ai = nullptr;
    int currentPlayer = 1;
    Board board;
    int turn = 0;
};


#endif //PA2_HEARTHSTONE_GAMEMANAGER_H
