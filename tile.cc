#include "tile.h"
#include <utility>
#include <locale>
#include <iostream>
using namespace std;

vector<pair<int, int>> Tile::possibleCaptures(const pair<int, int> &posn, Board &board) {
    vector<pair<int, int>> possibleCaptures; // define variable for possible captures
    vector<pair<int, int>> pMoves = possibleMoves(posn, board); // determine the possible moves

    // determine which of the possible moves results in the capture of a piece
    for (auto m : pMoves) {
        if ((board.getTile(m)->getSymbol() != '_') || (board.getTile(m)->getSymbol() != ' ')) {
            possibleCaptures.push_back(m);
        }
    }

    // return the possibleCaptures
    return possibleCaptures;
}

vector<pair<int, int>> Tile::possibleChecks(const pair<int, int> &posn, Board &board){
    // Define variables
    vector<pair<int, int>> possibleChecks; // Define variable for possible checks
    vector<pair<int, int>> possiblemoves = possibleMoves(posn, board); // Define variable for possible moves
    vector<pair<int, int>> possiblecaptures; // Define variable for possible captures
    Tile *piece; // Define variable to store what is at that tile
    int currTurn = board.getCurrTurn(); // Define a variable to store who's turn it is
    char opponentKing = (currTurn % 2 == 0) ? 'k' : 'K'; // Define variable for the opponent King

    // Iterate through possibleMoves one by one
    for (auto &move: possiblemoves){
        Board tempboard = board;

        // Simulate the move
        piece = tempboard.getTile(move);
        tempboard.removeTile(move);
        tempboard.addTile(piece->getSymbol(), move);
        tempboard.removeTile(posn);

        // Iterate through each possible capture and determine if a possible capture is opponentKing
        possiblecaptures = possibleCaptures(move, tempboard);
        for(const pair<int, int> &capture : possiblecaptures){
            piece = tempboard.getTile(capture);
            
            if(piece->getSymbol() == opponentKing){
                possibleChecks.push_back(move);
                break; // Can not check multiple times in the same position
            }
        }
    }

    // Return the possibleChecks
    return possibleChecks;
}

bool Tile::simulateMove(const pair<int, int> &posn1, const pair<int, int> &posn2, Board &board, Tile* piece) {
    Board tempboard = board; // create temporary board as to not modify the original
    
    // execute the move on the temporary board
    cout << "Simulating a move from [" << posn1.first + 1 << ", " << posn1.second + 1 << "] to [" << posn2.first + 1 << ", " << posn2.second + 1 << "]" << endl;
    tempboard.removeTile(posn2);
    piece = board.getTile(posn1);
    tempboard.addTile(piece->getSymbol(), posn2);
    tempboard.removeTile(posn1);

    // return false if the player is not in check on the temporary board
    return (tempboard.inCheck(tempboard) > 0);
}
