#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "computer.h"
using namespace std;

class Level2 : public Computer {
  public:
    Level2(string colour) : Computer{colour} {};
    vector<string> getMove(Board &board) override;
};

#endif
