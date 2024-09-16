#include "game.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "window.h"
#include "human.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
using namespace std;

int main() {
    // grab inputs repeatedly looking for "setup" or "game <white-player> <black-player>"
    Game game = Game{nullptr, nullptr};

    while (true) {
        bool setup = false;
        while (true) {
            cout << "Command: ";

            string input;
            getline(cin, input);

            cout << endl << endl;

            // if (setup)
	        //     cout << "______________________________________________________________________" << endl << endl;

            if (input == "setup") {
                if (game.gamesPlayed() > 0) {
                    game.resetGame();
                }

                game.setupGame();

				cout << "Please start a game with the command 'game <white-player> <black-player>', or re-enter setup mode with 'setup'." << endl;

                if (game.getFinish()) {
                    return 0;
                }

                setup = true;

            } else {
                stringstream tokenize(input);
                vector<string> args;
                string arg;

                while(getline(tokenize, arg, ' ')) {
                    args.push_back(arg);
                }

                if (args.size() == 0){ 
                    game.finish();
                    return 0;
                }

                if (args.size() != 3) {
                    cout << "Invalid Command: incorrect number of arguments" << endl;
                    continue;
                }

                if (args.at(0) != "game") {
                    cout << "Invalid Command: not a valid command" << endl;
                    continue;
                }

                if ((game.gamesPlayed() > 0) && (!setup)) {
                    game.resetGame();
                }

                for (int i = 1; i < 3; ++i) {
                    string colour = (i == 1) ? "white": "black";

                    if (args.at(i) == "human" ) {
                        Human *player = new Human;
                        game.getPlayer(i) = player;

                    } else if (args.at(i) == "computer1") {
                        Level1 *player = new Level1;
                        game.getPlayer(i) = player;

                    } else if (args.at(i) == "computer2") {
                        Level2 *player = new Level2;
                        game.getPlayer(i) = player;

                    } else if (args.at(i) == "computer3") {
                        Level3 *player = new Level3;
                        game.getPlayer(i) = player;
                    }
                }

                if (game.getPlayer(1) == nullptr || game.getPlayer(2) == nullptr) {
                    cout << "Invalid Command: incorrect player names" << endl;
                    delete game.getPlayer(1);
                    delete game.getPlayer(2);
                    continue;
                }

                cout << endl << "____________________________________________________________________" << endl << endl;
                game.startGame();

                if (game.getFinish()) {
                    return 0;

                } else {
                    cout << "Start a new game with the command 'game <white-player> <black-player>' or 'setup', or quit by pressing 'Ctrl-D'." << endl;
                    break;
                }
            }
        }
        
    }
}
