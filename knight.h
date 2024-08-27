#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "tile.h"
using namespace std;

class Knight : public Tile {
    bool justMoved = false;
  public:
    Knight(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { justMoved = torf; }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
