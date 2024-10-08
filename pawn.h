#ifndef _PAWN_H_
#define _PAWN_H_

#include "tile.h"
using namespace std;

class Pawn : public Tile {
    bool justMoved2 = false;
    void possibleEnPassant(const pair<int, int> &posn, Board &board, vector<pair<int, int>> &possiblemoves);
  public:
    Pawn(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { 
        Tile::setJustMoved(torf);
        if(!getMoved() && torf){
            setMoved(torf);
        }
    }
    void setJustMoved2(bool torf) override { justMoved2 = torf; }
    bool getJustMoved2() override { return justMoved2; }
    Tile* clone() override;
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
};
#endif
