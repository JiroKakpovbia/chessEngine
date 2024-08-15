#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include "level3.h"
#include "computer.h"
#include "player.h"
#include "tile.h"
using namespace std;

std::vector<string> Level3::getMove(Board &board) {
    string input;
    cin >> input;

    vector<Tile*> pieces;
    vector<pair<int, int>> safeMoves;
    vector<pair<int, int>> moves;
    vector<pair<int, int>> capturesChecksAndSafeMoves;
    Tile* fromTile = nullptr;
    pair<int, int> fromCoords;
    pair<int, int> toCoords;

    if (getColour() == "white") pieces = board.getActiveWhite(); // the Computer owns the White Pieces
    else pieces = board.getActiveBlack(); // the Computer owns the Black Pieces

    if (pieces.empty()) return vector<string>{"none"};

    // shuffle the pieces to ensure random selection
    random_shuffle(pieces.begin(), pieces.end());

    // check every piece to see if any moves can be made to avoid capture, capture another piece, or check the opponent
    for (auto *piece : pieces) {
        // get the coordinates of the piece
        for (int x = 0; x < board.getBoardSize(); ++x) {
            for (int y = 0; y < board.getBoardSize(); ++y) {
                if (board.getBoard()[x][y] == piece) { // check if the given piece is found on the board
                    fromCoords = {x, y}; // store coordinates of this piece
                    capturesChecksAndSafeMoves = piece->possibleCaptures(fromCoords, board, true); // check all the possible captures of the piece

                    vector<pair<int, int>> checks = piece->possibleChecks(fromCoords, board);
                    capturesChecksAndSafeMoves.insert(capturesChecksAndSafeMoves.end(), checks.begin(), checks.end()); // append all the possible checks of the piece
                }
            }
        }

        // check the possible moves on the board that can capture the piece
        for (int x = 0; x < board.getBoardSize(); ++x) {
            for (int y = 0; y < board.getBoardSize(); ++y) {
                if ((board.getBoard()[x][y]->getSymbol() != ' ') || (board.getBoard()[x][y]->getSymbol() != '_')) {
                    vector<pair<int, int>> captures = board.getBoard()[x][y]->possibleCaptures({x, y}, board, true);

                    if (find(captures.begin(), captures.end(), fromCoords) != captures.end()) { // if this piece is in danger of being captured
                        moves = piece->possibleMoves(fromCoords, board);

                        for (auto move : moves) { // check all the different possible moves for the piece
                            if (find(captures.begin(), captures.end(), move) == captures.end()) { // check if any of this piece's moves will keep it in danger of being captured
                                safeMoves.push_back(move);
                            }
                        }

                        capturesChecksAndSafeMoves.insert(capturesChecksAndSafeMoves.end(), safeMoves.begin(), safeMoves.end()); // append all the possible moves that avoid capture of the piece

                        if (!capturesChecksAndSafeMoves.empty()) { // check if no captures or checks can be made and there are no moves to avoid capture
                            fromTile = piece;
                            break;
                        }
                    }
                }
            }

            if (fromTile) break; // if a valid piece was found
        }

        if (fromTile) break; // if a valid piece was found
    }

    if (fromTile && !(capturesChecksAndSafeMoves.empty())) { // check if a piece was found and there exists at least one possible move to avoid capture, capture, or check another piece
        // pick a random move to avoid capture, capture, or check another piece from the possible moves
        int randomMove = rand() % capturesChecksAndSafeMoves.size();
        toCoords = capturesChecksAndSafeMoves[randomMove];

    } else { // check if no pieces were found or the final piece has no possible moves to avoid capture, capture, or check another piece
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

    // pick a random move from the possible moves
    int randomMove = rand() % moves.size();
    toCoords = moves[randomMove];

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
