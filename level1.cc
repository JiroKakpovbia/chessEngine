// Level1: The computer makes random legal moves, regardless of the outcome
#include <iostream>
#include <cstdlib>
#include "level1.h"
#include "tile.h"
using namespace std;

std::vector<string> Level1::getMove(Board &board) {
    vector<Tile*> pieces;
    vector<pair<int, int>> moves;
    Tile* fromTile = nullptr;
    pair<int, int> fromCoords;

    if ((board.getCurrTurn() % 2) == 0) pieces = board.getActiveWhite(); // the Computer owns the White Pieces
    else pieces = board.getActiveBlack(); // the Computer owns the Black Pieces

    if (pieces.empty()) return vector<string>{"none"};

    // shuffle the pieces to ensure random selection
    random_shuffle(pieces.begin(), pieces.end());

    // check every piece to see if a move can be made
    for (auto *piece : pieces) {
        for (int x = 0; x < board.getBoardSize(); ++x) {
            for (int y = 0; y < board.getBoardSize(); ++y) {
                if (board.getBoard()[x][y] == piece) { // check if the given piece is found on the board
                    fromCoords = make_pair(x, y); // store coordinates of this piece
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

    // pick a random move from the possible moves
    int randomMove = rand() % moves.size();
    pair<int, int> toCoords = moves[randomMove];

    // convert the coordinates to a string
    string from;
    from += static_cast<char>(fromCoords.first + 'a');
    from += to_string(fromCoords.second + 1);
    
    string to;
    to += static_cast<char>(toCoords.first + 'a');
    to += to_string(toCoords.second + 1);

    // decide if pawn promotion is available
    string promo;
    if (((board.getTile(fromCoords)->getSymbol() == 'P') || (board.getTile(fromCoords)->getSymbol() == 'p')) &&
    ((toCoords.second == 0) || (toCoords.second == 7))) {
        vector<string> promoOptions{"Q", "R", "B", "N"};
        int promoChoice = rand() % 4;
        promo = promoOptions[promoChoice];
    }
    
    return vector<string>{"move", from, to, promo};
}
