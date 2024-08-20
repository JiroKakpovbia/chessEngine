#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <string>
#include "board.h"

class Player {
	public:
	virtual std::vector<string> getMove(Board &board) = 0;
	Player() = default;
	virtual ~Player() = default;
};
#endif
