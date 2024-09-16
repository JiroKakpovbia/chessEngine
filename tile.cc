#include "tile.h"
#include "king.h"
#include <utility>
#include <locale>
#include <iostream>
using namespace std;

vector<pair<int, int>> Tile::possibleMoves(const pair<int, int> &posn, Board &board) {
    vector<pair<int, int>> vec;
    return vec;
}

vector<pair<int, int>> Tile::possibleCaptures(const pair<int, int> &posn, Board &board) {
    vector<pair<int, int>> possibleCaptures; // define variable for possible captures
    setSimulating(true); // avoid infinite recursion
    vector<pair<int, int>> pMoves = possibleMoves(posn, board); // determine the possible moves
    setSimulating(false); // avoid infinite recursion

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
    int currTurn = board.getCurrTurn(); // Define a variable to store who's turn it is
    char opponentKing = (currTurn % 2 == 0) ? 'k' : 'K'; // Define variable for the opponent King

    // Iterate through possibleMoves one by one
    for (auto &move: possiblemoves){
        Board tempboard = board;

        // Simulate the move
        Tile *piece = tempboard.getTile(move); // Define variable to store what is at that tile
        char symbol = piece->getSymbol(); // Define variable to store the symbol of the tile
        tempboard.removeTile(move);
        tempboard.addTile(symbol, move);
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

bool Tile::simulateMove(const pair<int, int> &posn1, const pair<int, int> &posn2, Board &board) {
    if (isSimulating) return false; // prevents infinite recursion

    Board temp = board; // create temporary board as to not modify the original
    Tile *piece = temp.getTile(posn1);
    char symbol = piece->getSymbol(); // the piece's symbol

    // simulate the move on a temporary board
    temp.removeTile(posn2);
    temp.addTile(symbol, posn2);
    temp.removeTile(posn1);

    // return true if the player is in check, false otherwise
    return (temp.inCheck(temp));
}
