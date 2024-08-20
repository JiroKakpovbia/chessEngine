#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include "player.h"
#include "history.h"
#include "board.h"
#include "studio.h"
#include "window.h"

class Game {
	Player *whitePlayer;
	Player *blackPlayer;
	Board *board;
	History *history;
	Studio *studio;
	std::vector<Observer *> obs;
	Xwindow *window;
	static inline float whiteWins = 0;
	static inline float blackWins = 0;
	void printScore();
	bool checkValid();
	void simplePrint(std::pair<int, int> beg, std::pair<int, int> end);
	static inline bool final = false;
public:
	Game(Player *white, Player *black, Xwindow *window);
	~Game();
	Player *&getPlayer(int playerNum);
	void startGame();
	void setupGame();
	Board *&getBoard();	
	void finish() {final = true;}
	bool getFinish() {return final;}
};

#endif
