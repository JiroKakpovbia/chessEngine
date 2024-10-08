#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include "board.h"
using namespace std;

class Board;

class Tile {
    char symbol;
    bool moved = false;
    bool justMoved = false;
    bool isSimulating = false;
  public:
    Tile(char symbol) : symbol{symbol} {}
    virtual ~Tile() {}
    char getSymbol() const { return symbol; }
    void setSymbol(char sym) { symbol = sym; }
    virtual bool getMoved() { return moved; }
    virtual void setMoved(bool torf) { moved = torf; }
    virtual bool getJustMoved() { return justMoved; }
    virtual void setJustMoved(bool torf) { justMoved = torf; }
    virtual bool getJustMoved2() { return false; }
    virtual void setJustMoved2(bool torf) {}
    virtual void setSimulating(bool torf) { isSimulating = torf; }
    virtual bool getSimulating() { return isSimulating; }
    virtual Tile* clone() = 0;
    virtual vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board); // Finds all possible moves for that the player can make for a specific piece
    virtual vector<pair<int, int>> possibleCaptures(const pair<int, int> &posn, Board &board); // Finds all possible captures that the player can make for a specific piece
    virtual vector<pair<int, int>> possibleChecks(const pair<int, int> &posn, Board &board); // Finds all possible checks that the player can make for a specific piece
    virtual bool simulateMove(const pair<int, int> &posn1, const pair<int, int> &posn2, Board &board); // Returns false if the simulated move doesn't put the player in check, true otherwise
};

#endif
