#include <vector>
#include <string>
#include <cstdlib>
#include "level2.h"
#include "computer.h"
#include "player.h"
#include "tile.h"
#include <iostream>
using namespace std;

std::vector<string> Level2::getMove(Board &board) {
    string input;
    cin >> input;

    vector<Tile*> pieces;
    vector<pair<int, int>> moves;
    vector<pair<int, int>> capturesAndChecks;
    Tile* fromTile = nullptr;
    pair<int, int> fromCoords;
    pair<int, int> toCoords;

    if (getColour() == "white") pieces = board.getActiveWhite(); // the Computer owns the White Pieces
    else pieces = board.getActiveBlack(); // the Computer owns the Black Pieces

    if (pieces.empty()) return vector<string>{"none"};

    // shuffle the pieces to ensure random selection
    random_shuffle(pieces.begin(), pieces.end());

    // check every piece to see if a capture or check can be made
    for (auto *piece : pieces) {
        for (int x = 0; x < board.getBoardSize(); ++x) {
            for (int y = 0; y < board.getBoardSize(); ++y) {
                if (board.getBoard()[x][y] == piece) { // check if the given piece is found on the board
                    fromCoords = {x, y}; // store coordinates of this piece
                    capturesAndChecks = piece->possibleCaptures(fromCoords, board, true); // check all the possible captures of the piece

                    vector<pair<int, int>> checks = piece->possibleChecks(fromCoords, board);
                    capturesAndChecks.insert(capturesAndChecks.end(), checks.begin(), checks.end()); // append all the possible checks of the piece

                    if (!capturesAndChecks.empty()) { // check if no captures or checks can be made
                        fromTile = piece;
                        break;
                    }
                }
            }

            if (fromTile) break; // if a valid piece was found
        }

        if (fromTile) break; // if a valid piece was found
    }
    if (fromTile && !(capturesAndChecks.empty())) { // check if a piece was found and there exists at least one possible capture or check
        // pick a random capture or check from the possible moves
        int randomMove = rand() % capturesAndChecks.size();
        toCoords = capturesAndChecks[randomMove];

    } else { // check if no pieces were found or the final piece has no possible captures or checks
        // check every piece to see if a move can be made
        for (auto *piece : pieces) {
            for (int x = 0; x < board.getBoardSize(); ++x) {
                for (int y = 0; y < board.getBoardSize(); ++y) {
                    if (board.getBoard()[x][y] == piece) { // check if the given piece is found on the board
                        fromCoords = {x, y}; // store coordinates of this piece
                        moves = piece->possibleMoves(fromCoords, board); // check all the possible moves of the piece

                        if (!moves.empty()) { // if no moves can be made, check for the next piece
                            fromTile = piece;
                            break;
                        }
                    }
                }

                if (fromTile) break; // if a valid piece was found
            }

            if (fromTile) break; // if a valid piece was found
        }
         
        if (!fromTile || moves.empty()) { // if no pieces were found or the final piece has no possible moves
            return vector<string>{"none"};
        }

        // pick a random move from the possible moves
        int randomMove = rand() % moves.size();
        toCoords = moves[randomMove];
    }

    // convert the coordinates to a string
    string from;
    from += static_cast<char>(fromCoords.first + 'a');
    from += to_string(fromCoords.second + 1);
    
    string to;
    to += static_cast<char>(toCoords.first + 'a');
    to += to_string(toCoords.second + 1);

    // output the computer's move
    cout << "Computer moved [" << from << "] to [" << to << "]" << endl;

    return vector<string>{input, from, to};
}
