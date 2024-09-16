#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "tile.h"
using namespace std;

class Bishop : public Tile {
  public:
    Bishop(char symbol) : Tile{symbol} {};
    Tile* clone() override;
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
