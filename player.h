#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <string>
#include "board.h"


class Player {
	string colour;
	public:
	virtual std::vector<string> getMove(Board &board);
	string getColour();
	Player(string colour): colour{colour} {}
};
#endif
