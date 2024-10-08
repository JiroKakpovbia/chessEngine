#ifndef _BLANK_H_
#define _BLANK_H_

#include "tile.h"
using namespace std;

class Blank : public Tile {
  public:
    Blank(char symbol) : Tile{symbol} {};
    bool getJustMoved() override { return false; }
    Tile* clone() override {
      return new Blank(getSymbol());
    }
    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override {
      vector<pair<int, int>> vec;
      return vec;
    }
    vector<pair<int, int>> possibleCaptures(const pair<int, int> &posn, Board &board) override {
      vector<pair<int, int>> vec;
      return vec;
    }
    vector<pair<int, int>> possibleChecks(const pair<int, int> &posn, Board &board) override {
      vector<pair<int, int>> vec;
      return vec;
    }
    bool simulateMove(const pair<int, int> &posn1, const pair<int, int> &posn2, Board &board) override { return false; }
};
#endif
