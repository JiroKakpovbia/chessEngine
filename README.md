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

In the case of a computer player, the command move (without arguments) makes the computer player make a move.

'setup' enters setup mode, within which you can set up your own initial board configurations. This can only be done when a game is not currently running. Within setup mode, the following language is used:

'+ \<piece\> \<square\>' places the piece onto the board. Specifically, it places \<piece\> onto \<square\>. If a piece is already on that square, it is replaced.
  - eg. '+ K e1' places the piece K (i.e., White king in this case) on the square e1.

'- \<square\>' removes the piece from the parameter \<square\>. If there is no piece at that square, nothing happens.
  - eg. '- e1' removes the piece from e1.

'= \<colour\>' makes it colour’s turn to go next.
  - eg. '= black' makes it the Black player's turn to go next."


**Remember:** White pieces = UPPERCASE, Black pieces = lowercase

____________________________________________________________________
