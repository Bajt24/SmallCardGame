#ifndef PA2_HEARTHSTONE_GUI_H
#define PA2_HEARTHSTONE_GUI_H


#include "../Entities/Player.h"
#include "GameManager.h"
/**
 * Class that handles the console output representing the current board state
 */
class GUI {
public:
    GUI()=default;
    void draw(GameManager * g);
    static const int windowScale = 50;
private:
    Player * p1,*p2;
    Board * b;
    int * turn;
    /** Print spaces */
    void printSpaces(int num, std::stringstream * s);
    /** Metoda starající se o podrobný výpis hráče Prints a detailed output of player*/
    void drawPlayer(std::stringstream * ss, Player * p);
    /** Draws onboard minions and their stats*/
    void drawMinions(std::stringstream *ss,std::vector<Minion*>* a);
    void drawMiddleLine(std::stringstream *ss);

    void drawMinionsHead(std::stringstream *ss,std::vector<Minion*>* a, int totalSpace, int spaceMeziMinionama);
    void drawMinionsBody(std::stringstream *ss,std::vector<Minion*>* a, int totalSpace, int spaceMeziMinionama);
    void drawMinionsStats(std::stringstream *ss,std::vector<Minion*>* a, int totalSpace, int spaceMeziMinionama);

};


#endif //PA2_HEARTHSTONE_GUI_H
