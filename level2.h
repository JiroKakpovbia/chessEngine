#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include "player.h"
using namespace std;

class Level2 : public Player {
  public:
    Level2() : Player() {};
    vector<string> getMove(Board &board) override;
};

#endif
