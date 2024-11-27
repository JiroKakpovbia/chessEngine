# chessEngine
The CS246 Final Project - Chess + Enhancements
____________________________________________________________________
Welcome to Chess! Please choose from the following commands:

'game \<white-player\> \<black-player\>' starts a new game. The parameters \<white-player\> and \<black-player\> can be either human or computer[1-4].
  - eg. 'game human computer2' starts a game with the White player being Human and the Black player being a Computer.

'resign' concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.

'move \<start\> \<end\>' moves one of the pieces on the board. The parameters \<start\> and \<end\> specify the starting and ending coordinates of the piece to be moved.
  - eg. 'move e2 e4' moves the piece on e2 to e4.

Castling would be specified by the two-square move for the king.
  - eg. 'move e1 g1' (right castle) or 'move e1 c1' (left castle) for White.

Pawn promotion would additionally specify the piece type to which the pawn is promoted.
  - eg. 'move e7 e8 Q' moves a Pawn from e7 to e8 (the other end of the board), and subsequently makes it a Queen.

In the case of a computer player, the computer will make its move on its own.

'setup' enters setup mode, within which you can set up your own initial board configurations. This can only be done when a game is not currently running. Within setup mode, the following commands are used:

'+ \<piece\> \<square\>' places the piece onto the board. Specifically, it places \<piece\> onto \<square\>. If a piece is already on that square, it is replaced.
  - eg. '+ K e1' places the piece K (i.e., White king in this case) on the square e1.

'- \<square\>' removes the piece from the parameter \<square\>. If there is no piece at that square, nothing happens.
  - eg. '- e1' removes the piece from e1.

'= \<colour\>' makes it colour’s turn to go next.
  - eg. '= black' makes it the Black player's turn to go next."

'clear' removes every piece on the board.

'done' exits setup mode.

**Remember:** White pieces = UPPERCASE, Black pieces = lowercase

____________________________________________________________________
**Enhancements**:
1. Updated Pawn promotion
  - Can no longer promote at any square on the board
  - Pawn promotion works for both the Player and the Computer
  - Cannot promote to a piece of the opponent's colour
  - Turn switches to the opponent once a piece ia promoted
2. Modified Graphics to update with the Text display regarding Setup Mode and EnPassant
3. Added a "Clear" option in Setup Mode to clear the board, removing every piece present
4. Eliminated Computer move commands, making Computers move automatically
5. Added Tie/Stalemate
  - Added stalemate with no possible moves available for either player
  - Added tie by insufficient pieces on the board
6. Fixed the  Check detection system
  - Detection system when someone is in check, displaying in text and graphical display
  - Computers no longer make moves that put themselves in check
  - Double check is now detected, occurs when a piece is in check by 2 opposing pieces
7. Fixed long castling with Black pieces, now is possible
    Addressed excessive memory leaks, only leaks remaining are due to the XQuartz/XWindow functionalities
9. Added Blank tile subclass to make the Tile class abstract
10. Updated resign command to now prompt the user to play another game, ressetting the board as well
____________________________________________________________________
