#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "tile.h"
using namespace std;

class Knight : public Tile {
  public:
    Knight(char symbol) : Tile{symbol} {};
    Tile* clone() override;
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
