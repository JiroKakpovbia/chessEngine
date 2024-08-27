#ifndef _KING_H_
#define _KING_H_

#include "tile.h"
using namespace std;

class King : public Tile {
    bool justMoved = false;
    void possibleCastles(const pair<int, int> &posn, Board &board, vector<pair<int, int>> &possiblemoves);
  public:
    King(char symbol) : Tile{symbol} {};
    void setJustMoved(bool torf) override { 
        justMoved = torf;
        if(!getMoved() && torf){
            setMoved(torf);
        }
    }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override;
    vector<pair<int, int>> possibleChecks(const pair<int, int> &posn, Board &board) override;
};
#endif
