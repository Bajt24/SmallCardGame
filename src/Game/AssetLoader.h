#ifndef PA2_HEARTHSTONE_ASSETLOADER_H
#define PA2_HEARTHSTONE_ASSETLOADER_H


#include <string>
#include <vector>
#include "../Cards/Card.h"
/**
 * Class that handles loading card and deck presets from files.
 */
class AssetLoader {
public:
    AssetLoader()=default;
    virtual ~AssetLoader();
    /** Handles file loading, returs success boolean */
    bool load();
    /** Converts string to int */
    static int strToInt(std::string str);

    const std::vector<Card*> &getCards() const;

    const std::vector<Card*> getPl0Deck();
    const std::vector<Card*> getPl1Deck();


    const std::string cardsPath = "src/Assets/cards.txt";
    const std::string decksPath = "src/Assets/decks.txt";

private:
    std::vector<Card*> cards;
    std::vector<std::vector<Card*>> decks;
    int pl0selDeck = 0,pl1selDeck = 0;



    /** Verifies if selected decks are valid*/
    bool verifySelectedDecks() const;

    bool loadCards();
    bool parseCard(std::vector<std::string> arr, Card ** out);
    bool parseMinion(std::vector<std::string> arr, Card ** out);
    bool parseSpell(std::vector<std::string> arr, Card ** out);
    bool parseEffect(int effect, int param, Effect ** out);

    bool loadDecks();
    bool parseDeck(std::vector<std::string> * info);

};

#endif //PA2_HEARTHSTONE_ASSETLOADER_H
