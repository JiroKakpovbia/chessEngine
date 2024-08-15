#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "computer.h"
using namespace std;

class Level3 : public Computer {
  public:
    Level3(string colour) : Computer{colour} {};
    vector<string> getMove(Board &board) override;
};

#endif
