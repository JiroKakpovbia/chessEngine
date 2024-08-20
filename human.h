#ifndef HUMAN_H_
#define HUMAN_H_
#include "player.h"

class Human: public Player {
	public:
	std::vector<string> getMove(Board &board) override;
	Human() : Player() {}
};

#endif
