#ifndef _ROOK_H_
#define _ROOK_H_

#include "tile.h"
using namespace std;

class Rook : public Tile {
  public:
    Rook(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { 
        Tile::setJustMoved(torf);
        if(!getMoved() && torf){
            setMoved(torf);
        }
    }
    Tile* clone() override;
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
