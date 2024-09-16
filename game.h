#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include "subject.h"
#include "board.h"
#include "player.h"
#include "history.h"
#include "studio.h"
#include "window.h"
using namespace std;

class Game {
	Player *whitePlayer;
	Player *blackPlayer;
	Board *board;
	History *history;
	Studio *studio;
	vector<Observer *> obs;
	Xwindow *window;
	static inline float whiteWins = 0;
	static inline float blackWins = 0;
	void printScore();
	bool checkValid();
	void simplePrint(pair<int, int> beg, pair<int, int> end);
	static inline bool final = false;
public:
	Game(Player *white, Player *black);
	~Game();
	Player *&getPlayer(int playerNum);
	void startGame();
	void setupGame();
	void resetGame();
	Board *&getBoard();
	int gamesPlayed() { return (whiteWins + blackWins); }
	void finish() { final = true; }
	bool getFinish() { return final; }
};

#endif
