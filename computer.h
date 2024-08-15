#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <vector>
#include <string>
using namespace std;

class Computer : public Player {
  public:
    Computer(string colour) : Player{colour} {}
    virtual vector<string> getMove(Board &board) = 0;
};

#endif
