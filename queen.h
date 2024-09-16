#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "tile.h"
using namespace std;

class Queen : public Tile {
  public:
    Queen(char symbol) : Tile{symbol} {};
    Tile* clone() override;
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
