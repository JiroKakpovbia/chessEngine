#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "tile.h"
using namespace std;

class Bishop : public Tile {
    bool justMoved = false;
  public:
    Bishop(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { justMoved = torf; }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
