#ifndef PA2_HEARTHSTONE_GAME_H
#define PA2_HEARTHSTONE_GAME_H


#include "GameManager.h"
#include "Menu/Menu.h"
/**
 * This is the main class of the game instance.
 * The game is a simplified version of Hearthstone.
 *
 * The objective is to kill the other player. That can be done by building a strong board and by playing the right cards.
 * Key elements are Spells and Minions which cost your mana and can be played during your turn.
 * Player's mana is restored each round and increased by one.

 * The game supports match against other player and against computer.
 * The games can be saved/loaded and you can define your own cards in the preset.
 */
class Game {
public:
    Game();
};

#endif //PA2_HEARTHSTONE_GAME_H
