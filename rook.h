#ifndef _ROOK_H_
#define _ROOK_H_

#include "tile.h"
using namespace std;

class Rook : public Tile {
    bool moved = false;
    bool justMoved = false;
  public:
    Rook(char symbol) : Tile{symbol} {};
    bool Moved() override { return moved; }
    void setJustMoved(bool torf) override { 
        justMoved = torf;
        if(!moved && torf){
            moved = torf;
        }
    }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
