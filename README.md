# chessEngine
This is a Chess engine created using C++. It was created as a final project in the University of Waterloo's CS 246 (Object-Oriented Software Development) course offered in Spring 2024. My other teammates during the development of this project were Adam Muinuddin and Liam Knox.

The source code is unavailable in this public reposity as public access would violate academic policies. If you would like to see the source code for this project, please email me at jjkakpov@uwaterloo.ca and I will share the private repository.

Below, you can see the documentation containing the regulations for this assignment. Furthermore, there is a list of enhancements that I made individually after the assingment deadline had passed. Finally, the rules and instructions on how to play this Chess Engine are found at the end of this document. Note that the instructions are different than the one's specified in the assignment documentation.

Executing the "chess" file in the repository will start a new game. Have fun!


# Documentation
The final project guidelines for the CS 246 Spring 2024 offering that were followed can be accessed [here](./docs/project_guidelines.pdf).

The project guidelines specifically regarding Chess and instructions on how to play the game are [here](./docs/chess.pdf). Please note that modifications have been made, so the updated instructions can be found below.

A UML Class Diagram representing our software design for this Chess game can be found [here](./docs/uml_final.pdf).


# Enhancements
1. Can no longer promote at any square on the board
2. Pawn promotion works for both the Player and the Computer
3. Cannot promote to a piece of the opponent's colour
4. Turn switches to the opponent once a piece ia promoted
5. Modified Graphics to update with the Text display regarding Setup Mode and EnPassant
6. Added a "Clear" option in Setup Mode to clear the board, removing every piece present
7. Eliminated Computer move commands, making Computers move automatically
8. Added Tie/Stalemate
9. Added stalemate with no possible moves available for either player
10. Added tie by insufficient pieces on the board
11. Fixed the  Check detection system
12. Detection system when someone is in check, displaying in text and graphical display
13. Computers no longer make moves that put themselves in check
14. Double check is now detected, occurs when a piece is in check by 2 opposing pieces
15. Fixed long castling with Black pieces, now is possible
16. Addressed excessive memory leaks, only leaks remaining are due to the XQuartz/XWindow functionalities
17. Added Blank tile subclass to make the Tile class abstract
18. Updated resign command to now prompt the user to play another game, ressetting the board as well
19. Fixed issue where Pawns would jump over pieces in double forward move
20. Added images for each of the pieces in the graphical display (credit to [PNGEgg](https://www.pngegg.com/en/png-pdjoy) for the images)
____________________________________________________________________


# Rules and Instructions
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
