#ifndef HISTORY_H_
#define HISTORY_H_
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include "board.h"
#include "game.h"
using namespace std;

class History {
	stack<pair<pair<int, int>, pair<int, int>>> moveHistory;
	stack<char> tileHistory;
	stack<bool> promoHistory;
	public:
	void addHistory(pair<int, int> beg, pair<int, int> end, char taken, bool promo);
	void undo(Board *board, Game *game, vector<Observer *> obs);
};

#endif
