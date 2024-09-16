#include "king.h"
#include <iostream>
using namespace std;

Tile* King::clone() {
    King *newKing = new King(getSymbol());
    newKing->setMoved(getMoved());
    newKing->setJustMoved(getJustMoved());
    newKing->setSimulating(getSimulating());
    return newKing;
}

vector<pair<int, int>> King::possibleMoves(const pair<int, int> &posn, Board &board){
    // Define variables
    vector<pair<int, int>> possibleMoves; // Define variable for possible moves
    pair<int, int> posn2; // Define variable for posn2 to check moves
    Tile *piece; // Define variable to store what is at that tile
    int currTurn = board.getCurrTurn(); // Define a variable to store who's turn it is
    bool incheck = false; // Define a variable to store whether you are in check once a simulated move is made
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // Define a variable to store the directions a piece can move

    // Iterate through all moves the king can make
    for (auto &dir : directions) {
        posn2 = posn; // Reset the position of the piece

        posn2.first += dir.first; // Update the x coordinate
        posn2.second += dir.second; // Update the y coordinate

        // Ensure that the piece is still in bounds
        if (posn2.first < 0 || posn2.first > 7 || posn2.second < 0 || posn2.second > 7) continue;
        
        piece = board.getTile(posn2); // Get the tile stored at posn2 of the board

        // simulate the move on a temporary board, check if it leaves the player in check
        incheck = simulateMove(posn, posn2, board);

        if (!incheck){
            if(piece->getSymbol() != ' ' && piece->getSymbol() != '_'){
                if(currTurn % 2 == 0){ // White turn
                    if(islower(piece->getSymbol())){
                        possibleMoves.push_back(posn2);
                    } 
                    continue;
                } else { // Black turn
                    if(isupper(piece->getSymbol())){
                        possibleMoves.push_back(posn2);
                    } 
                    continue; 
                }
            }
            possibleMoves.push_back(posn2);
        }
    }

    // Determine if castling is possible
    possibleCastles(posn, board, possibleMoves);

    // Return the possiblemoves
    return possibleMoves;
}

vector<pair<int, int>> King::possibleChecks(const pair<int, int> &posn, Board &board){
    vector<pair<int, int>> vec;
    return vec;
}

void King::possibleCastles(const pair<int, int> &posn, Board &board, vector<pair<int, int>> &possiblemoves){
    // Ensure the king has not moved
    if (getMoved() || !((posn.second == 0 || posn.second == 7)) || !(posn.first == 4)) { return; }

    // Define variables
    pair<int, int> posn2; // Define variable for posn2 to check moves
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}}; // Only directions needed for castling
    int currTurn = board.getCurrTurn(); // Define a variable to store who's turn it is
    bool incheck = false; // Define a variable to store whether you are in check once a simulated move is made

    // Check for Right Castle
    // Ensure that our rook is to the right of the king
    Tile* rook = board.getTile({posn.first + 3, posn.second}); // store rook position
    if ((currTurn % 2 == 0 && rook->getSymbol() == 'R') || (currTurn % 2 == 1 && rook->getSymbol() == 'r')) { // Determine the turn
        if(!rook->getMoved()) {
            // Ensure that there are no pieces between the king and the rook
            Tile* space1 = board.getTile({posn.first + 1, posn.second});
            Tile* space2 = board.getTile({posn.first + 2, posn.second});

            if ((space1->getSymbol() == ' ' || space1->getSymbol() == '_') && (space2->getSymbol() == ' ' || space2->getSymbol() == '_')) {
                for (int i = 0; i <= 2; i++) { // Ensure that the king is not in check in the current position, posn + 1, posn + 2 
                    incheck = simulateMove(posn, {posn.first + i, posn.second}, board);
                    if(incheck) break;
                    else if (i == 2 && !incheck) {
                        posn2 = {posn.first + 2, posn.second};
                        possiblemoves.push_back(posn2); // Pushback posn2 to possiblemoves (valid move)
                        break;
                    }
                }
            }
        }
    }

    // Check for Left Castle
    // Ensure that our rook is to the right of the king
    rook = board.getTile({posn.first - 4, posn.second}); // store rook position
    if((currTurn % 2 == 0 && rook->getSymbol() == 'R') || (currTurn % 2 == 1 && rook->getSymbol() == 'r')){ // Determine the turn
        if(!rook->getMoved()){
            // Ensure that there are no pieces between the king and the rook
            Tile* space1 = board.getTile({posn.first - 1, posn.second});
            Tile* space2 = board.getTile({posn.first - 2, posn.second});
            Tile* space3 = board.getTile({posn.first - 3, posn.second});

            if ((space1->getSymbol() == ' ' || space1->getSymbol() == '_') && (space2->getSymbol() == ' ' || space2->getSymbol() == '_') && (space3->getSymbol() == ' ' || space3->getSymbol() == '_')) {
                for (int i = 0; i <= 2; i++) { // Ensure that the king is not in check in the current position, posn + 1, posn + 2, posn + 3
                    incheck = simulateMove(posn, {posn.first + i, posn.second}, board);
                    if(incheck) break;
                    else if (i == 2 && !incheck) {
                        posn2 = {posn.first - 2, posn.second};
                        possiblemoves.push_back(posn2); // Pushback posn2 to possiblemoves (valid move)
                        break;
                    }
                }
            }
        }
    }
}
