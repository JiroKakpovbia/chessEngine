#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include "board.h"
using namespace std;

class Board;

class Tile {
    char symbol;
    bool moved = false;
  public:
    Tile(char sym) : symbol{sym} {}
    virtual ~Tile() {}
    char getSymbol() const { return symbol; }
    void setSymbol(char sym) { symbol = sym; }
    virtual bool getMoved() { return moved; }
    virtual void setMoved(bool torf) { moved = torf; }
    virtual bool getJustMoved() { return false; }
    virtual void setJustMoved(bool torf) {}
    virtual bool getJustMoved2() { return false; }
    virtual void setJustMoved2(bool torf) {}
    virtual vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) = 0; // Finds all possible moves for that the player can make
    virtual vector<pair<int, int>> possibleCaptures(const pair<int, int> &posn, Board &board); // Finds all possible captures that the player can make
    virtual vector<pair<int, int>> possibleChecks(const pair<int, int> &posn, Board &board); // Finds all possible checks that the player can make
    virtual bool simulateMove(const pair<int, int> &posn1, const pair<int, int> &posn2, Board &board, Tile* piece); // Returns false if the simulated move doesn't put the player in check, true otherwise
};

#endif
