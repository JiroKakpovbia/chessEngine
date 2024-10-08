#include <sstream>
#include <utility>
#include "game.h"
#include "human.h"
#include "text.h"
#include "graphics.h"

Player *&Game::getPlayer(int playerNum) {
	if (playerNum == 1) return whitePlayer;
	return blackPlayer;
}

Game::Game (Player *white, Player *black): whitePlayer{white}, blackPlayer{black}, board{new Board}, history{new History}, studio{new Studio{board}}, window{new Xwindow{700, 700}} {
	cout << "______________________________________________________________________" << endl << endl;
	cout << "Welcome to Chess! Please wait while the board is being constructed..." << endl;
	
	Text *textScreen = new Text{studio};

	obs.push_back(textScreen);
	studio->attach(textScreen);
	textScreen->notify();

	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Graphics *tileScreen = new Graphics{x, y, studio, window};
			obs.push_back(tileScreen);
			tileScreen->notify();
		}
	}

	cout << endl << "Board construction is complete! Please enter one of the following commands:" << endl;
	cout << "'setup' or 'game <white-player> <black-player>'." << endl;
}

Game::~Game() {
	delete board;
	delete history;
	delete whitePlayer;
	delete blackPlayer;
	delete studio;
	delete window;

	// delete observers (text and graphical displays)
	for (auto it = obs.begin(); it != obs.end(); ++it) {
      delete *it;
  	}

	if (final) {
		printScore();
	}
}

void Game::simplePrint(pair<int, int> beg, pair<int, int> end) {
	studio->attach(obs.at(8 * beg.second + beg.first + 1));
	studio->attach(obs.at(8 * end.second + end.first + 1));
	studio->render();
	studio->detach(obs.at(8 * beg.second + beg.first + 1));
	studio->detach(obs.at(8 * end.second + end.first + 1));
}

void Game::startGame() {
	cout << "Each turn, you may choose from any of the following commands: 'undo', 'resign', or 'move <start> <end>'." << endl;

	Player *currPlayer;

	while (!board->draw() && !board->checkMate()) {
		currPlayer = (board->getCurrTurn() % 2 == 0) ? whitePlayer : blackPlayer; // determines the current player's turn

		if (board->inCheck(*board)) { // checks to see if the current player is in check
			string checkedPlayer = (currPlayer == whitePlayer) ? "White" : "Black";
			cout << checkedPlayer << " is in check!" << endl;
		}

		if (currPlayer == whitePlayer) // White's turn
			cout << "White's Turn: ";
		else // Black's turn
			cout << "Black's Turn: ";

		// determines who the current player is and reads their move
		vector<string> input = currPlayer->getMove(*board);

		if (input.size() == 0) {
			finish();
			return;
		}

		if (input.size() == 1) {
			if (input.at(0) == "resign") { // if a Player resigns, give the opposite Player the win
				break;

			} else if (input.at(0) == "undo") { // if a Player undoes their move, update the board history
				bool undid = history->undo(board, studio, obs);
				if (!undid)
					cout << "Improper command: there are no more moves to undo.";
				continue;
			}
		}

		if ((input.size() == 2) || (input.size() >= 5)) {
			cout << "Improper command: incorrect number of arguments." << endl;
			continue;
		}

		// the following assumes we have the correct number of arguments for a move to be made (3 for regular moves or 4 for pawn promotion)
		if (input.at(0) != "move") {
			cout << "Improper command: available commands are 'move', 'undo', or 'resign'." << endl;
			continue;
		}
	
		if (input.at(1).size() != 2) {
			cout << "Improper command: bad starting coordinate." << endl << endl;
			continue;
		}

		int x1 = (input.at(1))[0] - 'a';
		int y1 = (input.at(1))[1] - '1';
		pair<int, int> beg = make_pair(x1, y1);
		
		if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7) { // improper coord
			cout << "Improper command: bad starting coordinate." << endl << endl;
			continue;
		}

		if(input.at(2).size() != 2) {
			cout << "Improper command: bad ending coordinate." << endl << endl;
			continue;
		}
		
		int x2 = (input.at(2))[0] - 'a';
		int y2 = (input.at(2))[1] - '1';
		pair<int, int> end = make_pair(x2, y2);
		
		if (x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) { // improper coord
			cout << "Improper command: bad ending coordinate." << endl << endl;
			continue;
		}

		if ((input.size() == 3) || (input.size() == 4)) {
			char returned;
			char promo = 'X';

			if (input.size() == 3) {
				returned = board->makeMove(beg, end); // no pawn promotion

			} else {
				promo = (input.at(3))[0];
				returned = board->makeMove(beg, end, promo); // pawn promotion
			}

			// checking invalid inputs
			if (returned == 'X') { // character represents a failed move
				cout << "Improper command: move must be legal." << endl << endl;
				continue;

			} else if (returned == 'P') { // character represents a failed pawn promotion
				cout << "Improper command: valid pawn promotion must be made." << endl << endl;
				continue;
			}
			
			// add the valid move to the move history
			history->addHistory(beg, end, returned, promo);

			// output the move that was made
			string colour = (currPlayer == whitePlayer) ? "White" : "Black";
			string player = (dynamic_cast<Human*>(currPlayer)) ? "Human" : "Computer";
        	cout << endl << endl << colour << " " << player << " moved [" << input.at(1) << "] to [" << input.at(2) << "]";

			if ((returned == 'C') || (returned == 'c')) {
				cout << ", and castled";
			}

			if ((input.size() == 4) && ((board->getTile(end)->getSymbol() == promo))) { // output if the move was a promotion
				cout << ", and promoted their pawn to a ";

				if ((board->getTile(end)->getSymbol() == 'B') || (board->getTile(end)->getSymbol() == 'b')) {
					cout << "Bishop";

				} else if ((board->getTile(end)->getSymbol() == 'Q') || (board->getTile(end)->getSymbol() == 'q')) {
					cout << "Queen";

				} else if ((board->getTile(end)->getSymbol() == 'R') || (board->getTile(end)->getSymbol() == 'r')) {
					cout << "Rook";

				} else if ((board->getTile(end)->getSymbol() == 'N') || (board->getTile(end)->getSymbol() == 'n')) {
					cout << "Knight";
				}
			}

			cout << "." << endl;

			// updating the necessary Tiles on the board
			if (returned == 'e' || returned == 'E') { // update Tiles involved in en passant
				studio->attach(obs.at(8 * beg.second + beg.first));
				studio->attach(obs.at(8 * beg.second + beg.first + 2));
				simplePrint(beg, end);
				studio->detach(obs.at(8 * beg.second + beg.first));
				studio->detach(obs.at(8 * beg.second + beg.first + 2));

			} else if (returned == 'c' || returned == 'C') { // update Tiles involved in castling
				if (beg.first > end.first) { // short castle
					studio->attach(obs.at(8 * beg.second + beg.first));
					studio->attach(obs.at(8 * beg.second + beg.first - 1));
					studio->attach(obs.at(8 * beg.second + beg.first - 3));
					simplePrint(beg, end);
					studio->detach(obs.at(8 * beg.second + beg.first));
					studio->detach(obs.at(8 * beg.second + beg.first - 1));
					studio->detach(obs.at(8 * beg.second + beg.first - 3));

				} else { // long castle
					studio->attach(obs.at(8 * beg.second + beg.first + 2));
					studio->attach(obs.at(8 * beg.second + beg.first + 3));
					studio->attach(obs.at(8 * beg.second + beg.first + 4));
					simplePrint(beg, end);
					studio->detach(obs.at(8 * beg.second + beg.first + 2));
					studio->detach(obs.at(8 * beg.second + beg.first + 3));
					studio->detach(obs.at(8 * beg.second + beg.first + 4));
				}

			} else { // update Tiles involved in a regular move
				simplePrint(beg, end);
			}
		}

		board->setCurrTurn(board->getCurrTurn() + 1);
    	cout << "______________________________________________________________________" << endl << endl;
	}

	if (board->checkMate()) {
		cout << "Checkmate!" << endl << endl;	
		//window->drawString(400, 400, "Checkmate!", Xwindow::Black);

		if (currPlayer == whitePlayer) {
			++blackWins;
			cout << "Black has won!" << endl;
			//window->drawString(400, 400, "Black Wins!", Xwindow::Black);

		} else {
			++whiteWins;
			cout << "White has won!" << endl;
			//window->drawString(400, 400, "White Wins!", Xwindow::Black);
		}
	} else if (board->draw()) {
		whiteWins += 0.5;
		blackWins += 0.5;

		char indicator = board->draw();

		if (indicator == 'M') // no legal moves
			cout << "Stalemate! No legal moves remain.";
		else
			cout << "Draw! ";

		if (indicator == 'S') // insufficient material
			cout << "Insufficient materials to obtain checkmate.";

		else if (indicator == 'R') // three repeated moves
			cout << "The same position has occured three times with the same player to move and all possible moves identical.";

		else if (indicator == 'F') // fifty non-pawn moves
			cout << "50 consecutive moves have been made by both players without any pawn movement or piece capture.";

		cout << endl << endl << "It's a tie!" << endl;
		//window->drawString(70, 70, "Stalemate!", Xwindow::Black);

	} else {
		if (currPlayer == whitePlayer) {
			++blackWins;
			cout << endl << endl << "White has resigned." << endl << endl;
			cout << "Black has won!" << endl;
			//window->drawString(400, 400, "Black Wins!", Xwindow::Black);

		} else {
			++whiteWins;
			cout << endl << endl << "Black has resigned." << endl << endl;
			cout << "White has won!" << endl;
			//window->drawString(400, 400, "White Wins!", Xwindow::Black);
		}
	}

	cout << "______________________________________________________________________" << endl << endl;
}

void Game::setupGame() {
	cout << "Entering setup mode..." << endl;
	cout << "______________________________________________________________________" << endl << endl;
	cout << "You may choose from any of the following commands: '+ <piece> <square>', '- <square>', '= <colour>', or 'clear'." << endl;
	string input;

	while (true) {
		cout << "Command: ";
		if (!getline(cin, input)) {
			cout << endl;
			break;
		}
		cout << endl;

		stringstream tokenize(input);
		string arg1;

		if (!getline(tokenize, arg1, ' ')) {
			cout << "Improper command: no input given." << endl << endl;
			continue;		
		}
		
		if (arg1 == "done") {
			if(checkValid()) {
				cout << endl << "Exiting setup mode..." << endl << endl;
				return;

			} else {
				cout << "Invalid board: there must be one of each king, and no pawns in the outer rows." << endl;
				continue;
			}
		} else if (arg1 == "clear") {
			for (int x = 0; x < board->getBoardSize(); ++x) {
				for (int y = 0; y < board->getBoardSize(); ++y) {
					if ((board->getTile({x, y})->getSymbol() != '_') || (board->getTile({x, y})->getSymbol() != ' ')) {
						board->removeTile({x, y});
						studio->attach(obs.at(8 * x + y + 1));
					}
				}
			}
			studio->render();
			for (int x = 0; x < board->getBoardSize(); ++x) {
				for (int y = 0; y < board->getBoardSize(); ++y) {
					if ((board->getTile({x, y})->getSymbol() != '_') || (board->getTile({x, y})->getSymbol() != ' '))
						studio->detach(obs.at(8 * x + y + 1));
				}
			}
			cout << "______________________________________________________________________" << endl << endl;
			continue;
		}

		string arg2;
		if (!getline(tokenize, arg2, ' ')) {
			cout << "Improper command: no second argument." << endl << endl;
			continue;
		}

		if (arg1 == "+" && arg2.size() == 1) {
			string arg3;

			if (!getline(tokenize, arg3, ' ') || arg3.size() != 2) {
				cout << "Improper command: no coordinates." << endl << endl;
				continue;
			}

			int x = arg3[0] - 'a';
			int y = arg3[1] - '1';
			pair<int, int> location = make_pair(x, y);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				cout << "Improper command: bad coordinate." << endl << endl;
				continue;
			}

			board->addTile(arg2[0], location);
			studio->attach(obs.at(8 * location.second + location.first + 1));
			studio->render();
			studio->detach(obs.at(8 * location.second + location.first + 1));

		} else if (arg1 == "-") {
			int x = arg2[0] - 'a';
			int y = arg2[1] - '1';
			pair<int, int> location = make_pair(x, y);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				cout << "Improper command: bad coordinate." << endl << endl;
				continue;
			}

			board->removeTile(location);
			studio->attach(obs.at(8 * location.second + location.first + 1));
			studio->render();
			studio->detach(obs.at(8 * location.second + location.first + 1));

		} else if (arg1 == "="){
			if (arg2 == "black") {
				board->setCurrTurn(1);
				cout << endl << "It is now Black's turn." << endl;

			} else if (arg2 == "white") {
				board->setCurrTurn(0);
				cout << endl << "It is now White's turn." << endl;

			} else {
				cout << "Improper command: no valid player given." << endl << endl;
				continue;
			}
		} else {
			cout << "Improper command: Invalid beginning command or format." << endl << endl;
			continue;
		}

		cout << "______________________________________________________________________" << endl << endl;
	}
}

// Resets the board for a new game
void Game::resetGame() {
	// reset the players
	delete whitePlayer;
	delete blackPlayer;
	whitePlayer = nullptr;
	blackPlayer = nullptr;

	// reset the board
	delete board;
	board = nullptr;
	board = new Board;

	// reset the move history
	delete history;
	history = nullptr;
	history = new History();

	// reset the studio
	delete studio;
	studio = nullptr;
	studio = new Studio{board};

	// reset the window
	delete window;
	window = nullptr;
	window = new Xwindow{700, 700};

	// reset and redisplay the observers
	for (auto it = obs.begin(); it != obs.end(); ++it) {
		studio->detach(*it);
    	delete *it;
		*it = nullptr;
  	}

	obs.erase(obs.begin(), obs.end());

	Text *textScreen = new Text{studio};

	obs.push_back(textScreen);
	studio->attach(textScreen);
	textScreen->notify();

	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Graphics *tileScreen = new Graphics{x, y, studio, window};
			obs.push_back(tileScreen);
			tileScreen->notify();
		}
	}
}

// Player class needs to hold a win counter
void Game::printScore() {
	cout << endl << "Final Score:" << endl;
	cout << "White: " << whiteWins << endl;
	cout << "Black: " << blackWins << endl;	
}

// Returns the current board
Board *&Game::getBoard() {
	return board;
}

// Checks if the current board setup is valid (used for setup mode)
bool Game::checkValid() {
	int whiteKings = 0;
	int blackKings = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			char tile = (board->getTile(make_pair(i, j)))->getSymbol();
			if (tile == 'k') {
				++blackKings;	
			} else if (tile == 'K') {
				++whiteKings;
			} else if ((j == 0 || j == 7) && (tile == 'p' || tile == 'P')) {
				return false;
			}
		}	
	}
	if (blackKings && blackKings < 2 && whiteKings && whiteKings < 2) {
		return true;
	}
	return false;
}
