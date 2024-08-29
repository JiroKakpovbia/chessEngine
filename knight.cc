#include "knight.h"
#include <iostream>
using namespace std;

vector<pair<int, int>> Knight::possibleMoves(const pair<int, int> &posn, Board &board){
    // Define variables
    vector<pair<int, int>> possibleMoves; // Define variable for possible moves
    pair<int, int> posn2; // Define variable for posn2 to check moves
    Tile *piece; // Define variable to store what is at that tile
    int currTurn = board.getCurrTurn(); // Define a variable to store who's turn it is
    bool incheck = false; // Define a variable to store whether you are in check once a simulated move is made
    vector<pair<int, int>> directions = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}}; // Define a variable to store the directions a piece can move

    // Iterate through all moves the knight can make
    for (auto &dir : directions){
        posn2 = posn; // Reset the position of the piece 

        posn2.first += dir.first; // Update the x coordinate
        posn2.second += dir.second; // Update the y coordinate

        // Ensure that the piece is still in bounds
        if (posn2.first < 0 || posn2.first > 7 || posn2.second < 0 || posn2.second > 7) continue;
        
        piece = board.getTile(posn2); // Get the tile stored at posn2 of the board

        // simulate the move on a temporary board, check if it leaves the player in check
        incheck = simulateMove(posn, posn2, board, piece);

        if(!incheck){
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

    // Return the possibleMoves
    return possibleMoves;
}
