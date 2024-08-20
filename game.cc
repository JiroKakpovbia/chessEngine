#include <sstream>
#include <utility>
#include "game.h"
#include "human.h"
#include "text.h"
#include "graphics.h"
using namespace std;

Player *&Game::getPlayer(int playerNum) {
	if (playerNum == 1) return whitePlayer;
	return blackPlayer;
}

Game::Game (Player *white, Player *black, Xwindow *window): whitePlayer{white}, blackPlayer{black}, board{new Board}, history{new History}, studio{new Studio{board}}, window{window} {
	cout << "____________________________________________________________________" << endl;
	cout << endl << "Welcome to Chess! Please enter one of the following commands:" << endl;
	cout << "'setup' or 'game <white-player> <black-player>'." << endl;
	cout << "____________________________________________________________________" << endl;
	
	Text *textScreen = new Text{studio};

	obs.push_back(textScreen);
	studio->attach(textScreen);
	textScreen->notify();

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			Graphics *tileScreen = new Graphics{x, y, studio, window};
			obs.push_back(tileScreen);
			//studio->attach(tileScreen);
			tileScreen->notify();
		}
	}
}

Game::~Game() {
	delete board;
	delete history;
	delete whitePlayer;
	delete blackPlayer;
	delete studio;
	for (auto it = obs.begin(); it != obs.end(); ++it) {
      delete *it;
  	}
	if (final) {
		printScore();
	}
}

void Game::simplePrint(pair<int, int> beg, pair<int, int> end) {
	studio->attach(obs.at(8 * beg.first + beg.second + 1));
	studio->attach(obs.at(8 * end.first + end.second + 1));
	studio->render();
	studio->detach(obs.at(8 * beg.first + beg.second + 1));
	studio->detach(obs.at(8 * end.first + end.second + 1));
}

void Game::startGame() {
	cout << "Each turn, you may choose from one of the following commands: 'undo', 'resign', or 'move <start> <end>'." << endl;

	Player *currPlayer;

	while (!board->checkMate() && !board->staleMate()) {
		if (board->getCurrTurn() % 2 == 0) // White's turn
			cout << endl << "White's Turn: ";
		else // Black's turn
			cout << endl << "Black's Turn: ";

		// determines who the current player is and reads their move
		vector<string> input;
		if (board->getCurrTurn() % 2 == 0) {
			currPlayer = whitePlayer;
			input = whitePlayer->getMove(*board);

		} else {
			currPlayer = blackPlayer;
			input = blackPlayer->getMove(*board);
		}

		if (input.size() == 0) {
			finish();
			return;
		}

		if (input.size() == 1) {
			if (input.at(0) == "resign") { // if a Player resigns, give the opposite Player the win
				break;

			} else if (input.at(0) == "undo") { // if a Player undoes their move, update the board history 
				history->undo(board, studio, obs);
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
			cout << "Improper command: bad starting coordinate." << endl;
			continue;
		}

		int x1 = (input.at(1))[0] - 'a';
		int y1 = (input.at(1))[1] - '1';
		pair<int, int> beg = make_pair(x1, y1);
		
		if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7) { // improper coord
			cout << "Improper command: bad starting coordinate." << endl;
			continue;
		}

		if(input.at(2).size() != 2) {
			cout << "Improper command: bad ending coordinate." << endl;
			continue;
		}
		
		int x2 = (input.at(2))[0] - 'a';
		int y2 = (input.at(2))[1] - '1';
		pair<int, int> end = make_pair(x2, y2);
		
		if (x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) { // improper coord
			cout << "Improper command: bad ending coordinate." << endl;
			continue;
		}

		char returned;

		if ((input.size() == 3) || (input.size() == 4)) {
			char promo;

			if (input.size() == 3) {
				returned = board->makeMove(beg, end); // no pawn promotion

			} else {
				promo = (input.at(3))[0];
				returned = board->makeMove(beg, end, promo); // pawn promotion
			}

			// checking invalid inputs
			if (returned == 'X') { // character represents a failed move
				cout << "Improper command: move must be legal." << endl;
				continue;

			} else if (returned == 'P') { // character represents a failed pawn promotion
				cout << "Improper command: valid pawn promotion must be made." << endl;
				continue;
			}
			
			// add the valid move to the move history
			history->addHistory(beg, end, returned, false);

			// output the move that was made
			string colour = ((board->getCurrTurn() % 2) == 0) ? "White" : "Black";
			string player = (dynamic_cast<Human*>(currPlayer)) ? "Human" : "Computer";
        	cout << endl << colour << " " << player << " moved [" << input.at(1) << "] to [" << input.at(2) << "]";

			if ((input.size() == 4) && ((board->getTile(end)->getSymbol() == promo))) { // output if the move was a promotion
				cout << ", and promoted their pawn to a ";

				if (board->getTile(end)->getSymbol() == 'B') {
					cout << "Bishop";

				} else if (board->getTile(end)->getSymbol() == 'Q') {
					cout << "Queen";

				} else if (board->getTile(end)->getSymbol() == 'R') {
					cout << "Rook";

				} else if (board->getTile(end)->getSymbol() == 'N') {
					cout << "Knight";
				}
			}

			cout << "." << endl;

			// updating the necessary Tiles on the board
			if (returned == 'e' || returned == 'E') { // update Tiles involved in en passant
				studio->attach(obs.at(beg.second * 8 + end.first - beg.first * 2 + 1));
							// add other tiles
				simplePrint(beg, end);
				studio->detach(obs.at(beg.second * 8 + end.first - beg.first * 2 + 1));
							// add other tiles
			} else if (returned == 'c' || returned == 'C') { // update Tiles involved in castling
				if (beg.first > end.first) {
					// short castle
					studio->attach(obs.at(beg.second * 8 + beg.first + 3));
					studio->attach(obs.at(beg.second * 8 + beg.first + 5));
					simplePrint(beg, end);
					studio->detach(obs.at(beg.second * 8 + beg.first + 3));
					studio->detach(obs.at(beg.second * 8 + beg.first + 5));

				} else {
					// long castle
					studio->attach(obs.at(beg.second * 8 + beg.first));
					studio->attach(obs.at(beg.second * 8 + beg.first - 3));
					simplePrint(beg, end);
					studio->detach(obs.at(beg.second * 8 + beg.first));
					studio->detach(obs.at(beg.second * 8 + beg.first - 3));
				}
			} else { // update Tiles involved in a regular move
				simplePrint(beg, end);
			}
		}

		board->setCurrTurn(board->getCurrTurn() + 1);
    	cout << "____________________________________________________________________" << endl;
	}

	if (board->checkMate()) {
		cout << endl << "Checkmate!" << endl << endl;	
		window->drawString(400, 400, "Checkmate!", Xwindow::Black);

		if (board->getCurrTurn()%2 == 0) {
			++blackWins;
			cout << "Black has won!" << endl;
			window->drawString(400, 400, "Black Wins!", Xwindow::Black);

		} else {
			++whiteWins;
			cout << "White has won!" << endl;
			window->drawString(400, 400, "White Wins!", Xwindow::Black);
		}
	} else if (board->staleMate()) {
		whiteWins += 0.5;
		blackWins += 0.5;
		cout << endl << "Stalemate!" << endl << endl;
		cout << "It's a tie!" << endl;
		window->drawString(70, 70, "Stalemate!", Xwindow::Black);

	} else {
		if (board->getCurrTurn()%2 == 0) {
			++blackWins;
			cout << endl << "Black has won!" << endl;
			window->drawString(400, 400, "Black Wins!", Xwindow::Black);

		} else {
			++whiteWins;
			cout << endl << "White has won!" << endl;
			window->drawString(400, 400, "White Wins!", Xwindow::Black);
		}
	}
}

void Game::setupGame() {
	string input;

	while (getline(cin, input)) {
		stringstream tokenize(input);
		string arg1;

		if (!getline(tokenize, arg1, ' ')) {
			cout << "Improper command: no input given." << endl;
			continue;		
		}
		
		if (arg1 == "done") {
			if(checkValid()) {
				cout << "Exiting setup mode..." << endl;
				return;

			} else {
				cout << "Invalid board: there must be one of each king, and no pawns in the outer rows." << endl;
				continue;
			}
		}

		string arg2;
		if (!getline(tokenize, arg2, ' ')) {
			cout << "Improper command: no second argument." << endl;
			continue;
		}

		if (arg1 == "+" && arg2.size() == 1) {
			string arg3;
			if (!getline(tokenize, arg3, ' ') || arg3.size() != 2) {
				cout << "Improper command: no coordinates." << endl;
				continue;
			}

			int x = arg3[0] - 'a';
			int y = arg3[1] - '1';
			pair<int, int> location = make_pair(x, y);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				cout << "Improper command: bad coordinate." << endl;
				continue;
			}
			board->addTile(arg2[0], location);
			studio->attach(obs.at(location.first + 8 * location.second + 1));
			studio->render();
			studio->detach(obs.at(location.first + 8 * location.second + 1));

		} else if (arg1 == "-") {
			int x = arg2[0] - 'a';
			int y = arg2[1] - '1';
			pair<int, int> location = make_pair(x, y);

			if (x < 0 || x > 7 || y < 0 || y > 7) {
				cout << "Improper command: bad coordinate." << endl;
				continue;
			}

			board->removeTile(location);
			studio->attach(obs.at(location.first + 8 * location.second + 1));
			studio->render();
			studio->detach(obs.at(location.first + 8 * location.second + 1));

		} else if (arg1 == "="){
			if (arg2 == "black") {
				board->setCurrTurn(1);

			} else if (arg2 == "white") {
				board->setCurrTurn(0);

			} else {
				cout << "Improper command: no valid player given." << endl;
				continue;
			}

		} else {
			cout << "Improper command: Invalid beginning command or format." << endl;
		}
	}
}

// player class needs to hold a win counter
void Game::printScore() {
	cout << endl << "Final Score:" << endl;
	cout << "White: " << whiteWins << endl;
	cout << "Black: " << blackWins << endl;	
}

Board *&Game::getBoard() {
	return board;
}

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
