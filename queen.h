#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "tile.h"
using namespace std;

class Queen : public Tile {
    bool justMoved = false;
  public:
    Queen(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { justMoved = torf; }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
