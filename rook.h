#ifndef _ROOK_H_
#define _ROOK_H_

#include "tile.h"
using namespace std;

class Rook : public Tile {
    bool justMoved = false;
  public:
    Rook(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { 
        justMoved = torf;
        if(!getMoved() && torf){
            setMoved(torf);
        }
    }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
