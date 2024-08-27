#ifndef _BLANK_H_
#define _BLANK_H_

#include "tile.h"
using namespace std;

class Blank : public Tile {
  public:
    Blank(char symbol) : Tile{symbol} {};

    vector<pair<int, int>> possibleMoves(const pair<int, int> &posn, Board &board) override {
      vector<pair<int, int>> vec;
      return vec;
    }

    vector<pair<int, int>> possibleCaptures(const pair<int, int> &posn, Board &board, const bool secondcall) override {
      vector<pair<int, int>> vec;
      return vec;
    }

    vector<pair<int, int>> possibleChecks(const pair<int, int> &posn, Board &board) override {
      vector<pair<int, int>> vec;
      return vec;
    }
};
#endif