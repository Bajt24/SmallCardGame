#ifndef PA2_HEARTHSTONE_GAMESAVER_H
#define PA2_HEARTHSTONE_GAMESAVER_H


#include <map>
#include "GameManager.h"
/**
 * Class that handles loading and saving of current game instance
 */
class GameSaver {
public:
    /** Saves the current game state into file*/
    bool saveGame(std::string name, GameManager * g);
    /** Loads a game state from file*/
    bool loadGame(std::string name, GameManager ** g);
private:
    bool aiFlag = false;
    std::map<std::string,std::string> mapa;
    /** Checks when were the card presets modified*/
    bool getCardsModifiedDate(std::string path, long long * out);
    /** Check if key is in map*/
    bool mContains(std::string key);
    /** Check if keys are in map*/
    bool mContains(std::vector<std::string> keys);
    /** Returns value assigned to key*/
    std::string get(std::string key);
    /** Parses string input into vector of values*/
    std::vector<std::string> parseStr(std::string str);

    /** Serializes current player state*/
    void dumpPlayer(Player * p, int playerIndex,  const std::vector<Minion*>* m);
    void dumpPlayerHand(Player * p, int playerIndex);
    void dumpPlayersDeck(Player * p, int playerIndex);
    void dumpPlayersBoard(const std::vector<Minion*> * b, int playerIndex);
    bool dumpCardsModified(std::string path);
    void dumpGameManager(GameManager * g);

    /** Function that loads key-value pairs from file*/
    bool parseLines(std::string name);
    /** Handles the conversion from string to Player instance*/
    bool loadPlayer(int playerIndex,Player * p, Board * b, const std::vector<Card*> * prefabs);

    bool loadGameManager(GameManager * g);
    bool loadPlayersHand(int playerIndex, int handsize, std::vector<Card*> * hand, const std::vector<Card*> * prefabs);
    bool loadPlayersDeck(int playerIndex, int decksize, std::vector<Card*> * deck, const std::vector<Card*> * prefabs);
    bool loadPlayersBoard(int playerIndex, int boardsize, std::vector<Minion*> * board, const std::vector<Card*> * prefabs);
};


#endif //PA2_HEARTHSTONE_GAMESAVER_H
