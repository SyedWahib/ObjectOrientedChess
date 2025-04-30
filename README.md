# ChessProjectYear1
A program that contains functionality for playing chess. Currently only with another player.

# The Plan File has been replaced by the design file

# Tests according to the project proposal


1) The program should display the board along with the board format whenever the 
program is run, and after every move. 

Testing Strategy:
Load the program, and then select 1

Test Expectation:
The user can see the board when running the program and selecting to start a game

Test Result:
Succesful

2) The program should inform the users which color makes the move next. 

Testing Strategy:
Load the program, then select 1

Test Expectation:
The user can see the program tell them when they load the program which color's move it is

Testing Result:
Succesful

3) The program should inform the users of format in which the move could be made in 
(Ex: E2, E4) 

Testing Strategy:
Load the program, then select 2
Alternatively, Load the program, select 1, make an invalid move

Test Expectation:
Can see the program show them the (Alphabet(row)+Number(column)) format

Test Result:
Successful

4) The program should include error handling for whenever the users make an invalid 
move or make a move out of turn 

Testing Strategy:
Load the Program, select 1, make an invalid move

Test Expectation:
Proper handling of invalid move notation, and the program tells them the (Alphabet(row)+Number(column)) format

Test Result:
Succesful


5) The program should recognise when a move results in check and inform the users 

Testing Strategy:
Load the program, select 1, make a move that puts the opponent in check

White: [e2-e4, d1-g4, g4-g5, g5-g6]
Black: [f7-f5, f5-f4, f4-f3, ]

Test Expectation:
The program informs the user "(Color) King is in check!"

Test Result:
Succesful


6) The program should recognise when a user gets checkmate or if it’s a stalemate and 
end the program 

Testing Strategy:
Load the program, select 1, make a move that puts the opponent in checkmate or play to a stalemate
Test for Checkmate: Scholar's Mate (4 move checkmate)

White: [e2-e4, f1-c4, d1-h5, h5-f7]
Black: [a7-a5, a5-a4, a4-a3]

Test for Stalemate: Sam Loyd (10 move Stalemate)

White: [c2-c4, h2-h4, d1-a4, a4-a5, a5-c7, c7-d7, d7-b7, b7-b8, b8-c8, c8-e6]
Black: [h7-h5, a7-a5, a8-a6, a6-h6, f7-f6, e8-f7, d8-d3, d3-h7, f7-g6]

Test Expectation:
The program displays "CHECKMATE! (Color) wins!" and returns to the main menu

Test Result:
Succesful


7) The program should save the result and how the board looks once checkmate is 
achieved. 

Testing Strategy:
Load the progam, select 1, make a move that puts the opponent in checkmate or play to a stalemate
Test for Checkmate: Scholar's Mate (4 move checkmate)

White: [e2-e4, f1-c4, d1-h5, h5-f7]
Black: [a7-a5, a5-a4, a4-a3]


Test Expectation:
The program saves the game and result in SavedGame.txt

Test Result:
Succesfully saves both in SavedGame.txt
