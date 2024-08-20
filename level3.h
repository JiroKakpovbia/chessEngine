#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include "player.h"
using namespace std;

class Level3 : public Player {
  public:
    Level3() : Player() {};
    vector<string> getMove(Board &board) override;
};

#endif
