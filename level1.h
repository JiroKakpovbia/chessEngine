#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "computer.h"
using namespace std;

class Level1 : public Computer {
  public:
    Level1(string colour) : Computer{colour} {};
    vector<string> getMove(Board &board) override;
};

#endif
