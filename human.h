#ifndef HUMAN_H_
#define HUMAN_H_
#include "player.h"
#include <vector>
#include <string>

class Human: public Player {
	public:
	std::vector<string> getMove(Board &board) override;
	Human(string colour): Player{Player(colour)} {}
};

#endif
