#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include "player.h"
using namespace std;

class Level1 : public Player {
  public:
    Level1() : Player() {};
    vector<string> getMove(Board &board) override;
};

#endif
