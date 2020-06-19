#include "Game.h"
#include "GameManager.h"
#include "GameSaver.h"

Game::Game() {
    GameManager * g = new GameManager();
    GameSaver gs;
    if (!g->load())
        return;
    GUI gui;
    Menu m = Menu(g,&gui, &gs);
    m.draw();
    delete g;
}
