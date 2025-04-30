#include "../../Headers/Board/Board.h"
#include <iostream>
#include <cctype>
#include <string>
#include <limits>
#include <algorithm>

Board::Board()
{
    for (int i =0; i < 8; i++)
    {
        for (int j = 0; j<8; j++)
        {
            chessBoard[i][j] = nullptr;
        }
    }
    setBoard(chessBoard);
}

Board::~Board()
{
    resetBoard(chessBoard);
}


void Board::resetBoard(std:: array<std:: array<Piece*, 8>, 8>& chessBoard)  // An array of 8 arrays of 8 pieces
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            delete chessBoard[i][j];
        }
    }
}

void Board::placePieces(std:: array <std::array<Piece*, 8>,8>& chessBoard)
{
    chessBoard[0][0] = new Rook(0, 0,'r','B');
    chessBoard[0][1] = new Knight(0,1,'h','B');
    chessBoard[0][2] = new Bishop(0,2,'b','B');
    chessBoard[0][3] = new Queen(0,3,'q','B');
    chessBoard[0][4] = new King(0,4,'k','B');
    chessBoard[0][5] = new Bishop(0,5,'b','B');
    chessBoard[0][6] = new Knight(0,6,'h','B');
    chessBoard[0][7] = new Rook(0,7,'r','B');

    for(int i= 0; i < 8; i++)
    {
        chessBoard[1][i] = new Pawn(1,i,'p','B');
        chessBoard[6][i] = new Pawn(6,i,'P','W');
    }

    chessBoard[7][0] = new Rook(7, 0,'R','W');
    chessBoard[7][1] = new Knight(7,1,'H','W');
    chessBoard[7][2] = new Bishop(7,2,'B','W');
    chessBoard[7][3] = new Queen(7,3,'Q','W');
    chessBoard[7][4] = new King(7,4,'K','W');
    chessBoard[7][5] = new Bishop(7,5,'B','W');
    chessBoard[7][6] = new Knight(7,6,'H','W');
    chessBoard[7][7] = new Rook(7,7,'R','W');
}

void Board::setBoard(std:: array<std:: array<Piece*, 8>, 8>& chessBoard)
{
    resetBoard(chessBoard);
    placePieces(chessBoard);
}

std::string Board:: displayBoardToString()
{
    std:: string boardString = "   A  B  C  D  E  F  G  H\n   ________________________\n";
    for (int i=0; i < 8; i++)
    {
        boardString += std:: to_string(8-i) + "| ";

        for (int j=0; j<8; j++)
        {
            if (chessBoard[i][j] == nullptr)
            {
                boardString += "   ";
            }
            else
            {
                boardString += chessBoard[i][j]->getPName();
                boardString += "  ";
            }
        }
        boardString += "|" + std::to_string(8-i) + "\n";
    }
    boardString += "   ________________________\n   A  B  C  D  E  F  G  H\n";
    return boardString;
}

void Board::displayBoard()
{
    std:: cout << displayBoardToString() << std:: endl;
}

void Board:: saveGame()
{
    std::ofstream writeToFile("SavedGame.txt");
    if (writeToFile.is_open())
    {
        writeToFile << displayBoardToString();
        writeToFile.close();
    }
    else
    {
        std:: cerr << "Error: Unable to open SavedGame.txt for writing";
    }
}
void Board:: saveGameResult (std:: string result)
{
    std::ofstream writeToFile("SavedGame.txt", std::ios::app);
    if (writeToFile.is_open())
    {
        writeToFile << "The game is " << result;
        writeToFile.close();
    }
    else
    {
        std:: cerr << "Error: Unable to open SavedGame.txt for appending";
    }
}

bool Board::movePiece()
{
    bool validFrom;
    bool validTo;
    int fromRow;
    int fromCol;

    do
    {
        validFrom = false;
        try 
        {

            std::string player = isWhiteTurn ? "White - " : "Black - ";
            std::cout << player << "Type 'Save' to save the game, Or 'Quit' to quit\nEnter the position of the piece you would like to move from: \n";
            std::cin >> fromPosition;

            // To convert uppercase as toupper wont work for string
            std:: string inputUpper = fromPosition;
            std::transform(inputUpper.begin(), inputUpper.end(), inputUpper.begin(), ::toupper);

            if (inputUpper=="SAVE")
            {
                saveGame();
                std:: cout << "Game succesfully saved inside SavedGame.txt" << std:: endl;
                // To ask for input again
                continue;
            }

            if(inputUpper == "QUIT")
            {
                return false;
            }

            if (fromPosition.length() != 2 || !isalpha(fromPosition[0]) || !isdigit(fromPosition[1]))
            {
                throw "Invalid format, please make sure your input is in the Alphabet+Number format (ex: E4 or e4)";
            }

            // This method changes the user's input for from position into rows and columns
            convertFromNotation(fromPosition);
            fromRow = newRow;
            fromCol = newCol;

            if (chessBoard[fromRow][fromCol] == nullptr)
            {
                throw "there is no piece at this position";
            }

            // To check if its the correct player's turn

            if ((isWhiteTurn && chessBoard[fromRow][fromCol]->getPColor() != 'W') ||
                (!isWhiteTurn && chessBoard[fromRow][fromCol]->getPColor() != 'B'))
            {
                std::string colorError = "Its not ";
                colorError += (chessBoard[fromRow][fromCol]->getPColor() == 'W') ? "White's" : "Black's";
                colorError += "turn to move";
                throw colorError;
            }
            // If the code reached this block, input is valid
            validFrom = true;

        }

        catch (const std::string& colorError)
        {
            std::cout << "Error: " << colorError << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        catch (const char* errorMessage)
        {
            std::cout << "Error: " << errorMessage << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        catch (...)
        {
            std:: cout << "An unexpected error occured" << std:: endl;          
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (!validFrom);


    Piece* movingPiece = chessBoard[fromRow][fromCol];

    do
    {   validTo = false;
        try
        {
            std::cout << "Type 'Back' to change the moving position\n'Save' to save the game, or 'quit' to go back to main menu\n\n"
            << "Enter the position you would like to move the pieceto(ex: E4)" << std:: endl;
            std::cin >> toPosition;

            // To convert uppercase as toupper wont work for string
            std:: string inputUpper = toPosition;
            std::transform(inputUpper.begin(), inputUpper.end(), inputUpper.begin(), ::toupper);

            if(inputUpper == "BACK")
            {   //MovePiece is called again
                return movePiece();
            }

            if (inputUpper == "SAVE")
            {
                saveGame();
                std:: cout << "Game succesfully saved inside SavedGame.txt" << std:: endl;
                continue;
            }

            if(inputUpper== "QUIT")
            {
                return false;
            }

            // To check whether the input format is correct
            if (toPosition.length() != 2 || !isalpha(toPosition[0]) || !isdigit(toPosition[1]))
            {
                throw "Invalid format, please maku sure your input is in the Alphabet+Number format (Ex: E4 or e4)";
            }

            convertFromNotation(toPosition);  // Modifying the variables

            auto movingPiece = chessBoard[fromRow][fromCol];

            // To check for castling
            bool isCastlingAttempt = false;
            if (toupper(movingPiece->getPName()) == 'K')
            {
                int rowDiff = abs(newRow - fromRow);
                int colDiff = abs(newCol - fromCol);
                // If king has moved sideways
                if (rowDiff == 0 && colDiff == 2)
                {
                    isCastlingAttempt = true;
                    // Determining the move for rook depending on left or right king move
                    int rookFromCol = (newCol > fromCol) ? 7 : 0;
                    int rookToCol = (newCol > fromCol) ? fromCol + 1 : fromCol - 1;

                    Piece* rook = chessBoard[fromRow][rookFromCol];

                    // Checking if King and Rook havent moved
                    if (!movingPiece->getFirstMoveState() || rook == nullptr || toupper(rook->getPName())!= 'R' || !rook->getFirstMoveState())
                    {
                        throw "Castling failed: King or Rook has already moved";
                    }

                    // Checking if path is clear between King and Rook
                    // +1 meaning one square right and -1 meaning one square left
                    int step = (rookFromCol > fromCol) ? 1:-1;
                    // if rookfromCol is larger, then 1 else -1 since we're walking towards
                    // the rook from the king's perspective
                    for (int c = fromCol + step; c != rookFromCol; c+= step)
                    {
                        if (chessBoard[fromRow][c] != nullptr)
                            throw "Castling failed: Path is not clear";
                    }

                    // Checking if King is not in check
                    if (isInCheck(movingPiece->getPColor()))
                    {
                        throw "Castling failed: Cannot castle while in check";
                    }

                    // Checking if the two squares king passes through are not attacked

                    char opponentColor = (movingPiece->getPColor() == 'W') ? 'B' : 'W';
                    if (isSquareAttacked(fromRow, fromCol + step, opponentColor) || isSquareAttacked(fromRow, newCol, opponentColor))
                    {
                        throw "Castling failed: King cannot land or pass through a checked square";
                    }

                    // Performing the castle since all checks are passed
                    // Moving King
                    chessBoard[newRow][newCol] = movingPiece;
                    chessBoard[fromRow][fromCol] = nullptr;
                    movingPiece->setRow(newRow);
                    movingPiece->setCol(newCol);
                    movingPiece->setFirstMoveState(false);

                    // Moving Rook
                    chessBoard[fromRow][rookToCol] = rook;
                    chessBoard[fromRow][rookFromCol] = nullptr;
                    rook->setRow(fromRow);
                    rook->setCol(rookToCol);
                    rook->setFirstMoveState(false);
                    
                    //Since the castle is succesful, we don't need move validation for this move
                    isWhiteTurn = !isWhiteTurn;
                    displayBoard();
                    return true;
                }
            }

            validateStandardMove(fromRow,fromCol,newRow,newCol);

            // Check Prevention

            // Prevent moving while checked
            // We need to simulate how the board will look
            // Will modify temporarily, and then restore board state

            // Stored the moving piece
            auto movingPieceTemp = chessBoard[fromRow][fromCol];
            //Will store either nullptr or the piece thats captured so that it can be returned later
            auto movedSquare = chessBoard[newRow][newCol];
            char currentPlayerColor = movingPieceTemp->getPColor();


            chessBoard[newRow][newCol] = movingPieceTemp;
            chessBoard[fromRow][fromCol] = nullptr;

            movingPieceTemp->setRow(newRow);
            movingPieceTemp->setCol(newCol);

            bool IsCheck = isInCheck(currentPlayerColor);  // Storing to check later

            chessBoard[fromRow][fromCol] = movingPieceTemp;
            chessBoard[newRow][newCol] = movedSquare;

            movingPieceTemp->setRow(fromRow);
            movingPieceTemp->setCol(fromCol);

            if (IsCheck)
            {
                throw "Invalid move: This move leaves you in check";
            }
            // End of Check Prevention


            validTo = true;


        }

        catch (const char* errorMessage)
        {
            std::cout << "Error: " << errorMessage << std::endl;
        }

    } while (!validTo);

    // Deleting captured piece
    if (chessBoard[newRow][newCol] != nullptr)
    {
        delete chessBoard[newRow][newCol];
    }

    // UPdating the board
    chessBoard[newRow][newCol] = chessBoard[fromRow][fromCol];
    // Pawn Promotion
    if (toupper(chessBoard[newRow][newCol]->getPName()) == 'P' && (newRow == 0 || newRow == 7))
    {
        PawnPromotion(newRow, newCol);
    }

    // Changing the piece attributes for new move validation
    chessBoard[fromRow][fromCol]->setRow(newRow);
    chessBoard[fromRow][fromCol]->setCol(newCol);
    chessBoard[fromRow][fromCol]->setFirstMoveState(false);

    // deleting the old piece
    chessBoard[fromRow][fromCol] = nullptr;

    //Switching Turns
    isWhiteTurn = !isWhiteTurn;

    char opponentColor = (isWhiteTurn ? 'W' : 'B');


    if (isStalemate(opponentColor))
    {
        displayBoard();
        saveGame();
        std:: string result = "STALEMATE! Its a draw";
        std::cout << result << std::endl;
        saveGameResult(result);

        return false;
    }

    else if (isCheckmate(opponentColor))
    {
        displayBoard();
        std:: string winningColor = (isWhiteTurn ? "White" : "Black");
        std:: string result = "CHECKMATE! \n" + winningColor + "wins!\n";
        std::cout << result<< std::endl;
        saveGame();
        saveGameResult(result);
        return false;
    }


    else if (isInCheck(opponentColor))
    {
        std::cout << "\n" << (isWhiteTurn ? "White" : "Black") << "King is in Check!" << std::endl;
    }


    displayBoard();
    return true;
}

std::string Board::convertToNotation(int row, int col)
{
    // 1) the alphabets are associated with the columns, a is 0, b is 1 so on
    // 2) Since the program calculates rows upside down, the player's 8 is our 0, subtract total with row
    const std::string letters[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    return letters[col]+std:: to_string(8-row);
}

void Board::convertFromNotation(std:: string notation)
{
    // This returns the index of the alphabet from the letters attribute as that is our column
    auto matchingColumn = letters.find(tolower(notation[0]));

    // npos is used to indicate the not found state when searching inside a string

    if (matchingColumn == std:: string :: npos)
    {
        throw "Invalid format, please make sure the alphabet is within the range of a-h";
    }
    //Sets the class member to the index
    newCol = matchingColumn;
    //Since the second character is 1-8, and we need to calculate the row, we just
    //subtract the ascii value of 0 from the second character as its a char, and conver to int
    int rowNum = notation[1] - '0';

    if (rowNum <1 || rowNum > 8)
    {
        throw "Invalid format, please make sure the number is within the range of 1-8";
    }

    newRow = 8- rowNum;
}

// Checks if the path between two squares is clear for linear moves, Rook, Bishop and Queen
bool Board::isPathClear(int fromRow, int fromCol, int toRow, int toCol)
{
    //calculates row and column steps
    //If the row/col to travel to is greater, then direction is 1, otherwise -1
    // if it stays in place, then 0
    int rowDirection = (toRow > fromRow) ? 1 : ((toRow < fromRow) ? -1 : 0);
    int colDirection = (toCol > fromCol) ? 1: ((toCol < fromCol) ? -1 : 0);

    // Starts from the next step
    int currentRow = fromRow + rowDirection;
    int currentCol = fromCol + colDirection;

    // Increments the steps until the move is reached
    while (currentRow != toRow || currentCol != toCol)
    {
        // If this row has a piece, then its occupied, so return false
        if (chessBoard[currentRow][currentCol] != nullptr)
        {
            return false;
        }
    // Increments the steps
    currentRow += rowDirection;
    currentCol += colDirection;
    }
    // No pieces blocking if it reaches here, so true
    return true;
}

// returns location of king
std::pair<int, int> Board::findKing(char kingColor) 
{
    // First determines character for king
    char kingChar = (kingColor == 'W') ? 'K' : 'k';

    // Then loop through entire board
    for (int r=0; r< 8; r++)
    {
        for (int c=0; c < 8; c++)
        {
            // If this square has the same king, then its location returned
            if (chessBoard[r][c] != nullptr && chessBoard[r][c]->getPName() == kingChar)
            {
                return {r,c};
            }
        }
    }
    // Doesn't return anything since its an impossibility

}

//This checks if any piece can attack a target square, needs the opposite color and row, column of the square
bool Board:: isSquareAttacked(int row, int col, char attackerColor)
{
    // first loop through the entire board
    for (int r= 0; r<8; r++)
    {
        for(int c= 0; c< 8; c++)
        {
            // If this square has a piece that is of the color of the attacker
            if (chessBoard[r][c] != nullptr &&
            chessBoard[r][c]-> getPColor() == attackerColor)
            {
                bool potentialAttack = false;
                char currentPieceName = toupper(chessBoard[r][c]->getPName());

                // Checking for pawns, since they attack differently

                if (currentPieceName == 'P')
                {
                    // Pawns only move forward up or down depending on their color
                    int direction = (attackerColor == 'W') ? -1 : 1;

                    // The pawn can only attack diagonally,
                    // first one is check for the row up or down depending on color
                    // Then it will check for the column right or left
                    if (r + direction == row && (c + 1 == col || c-1 == col))
                    {
                        potentialAttack = true;
                    }
                }
                // Since all other pieces can capture on every valid square
                else if (chessBoard[r][c]->isValidMove(row,col))
                {
                    if (currentPieceName != 'H')
                    {
                        // If the path to square from piece is blocked, then it can't be attacked
                        if (isPathClear(r,c,row,col))
                        {
                            potentialAttack = true;
                        }
                    }
                        
                    else
                    {   // Horses can jump pieces
                        potentialAttack = true;
                    }
                }

                if (potentialAttack)
                {
                    return true;
                }

            }
        }
    }
    //If it passes through all of them, then the square is safe
    return false;
}


// THIS METHOD WAS GENERATED WITH THE HELP OF A GEN AI ///////////////////////////////////////////////////////
// Only the Data structure and the tasks were outlined by AI, NO CODE WAS PROVIDED

// Used during checkmate and stalemate detection, checks if legal moves exist for a piece of the player's color
std::vector<std::tuple<int,int,int,int>> Board:: generatePossibleMoves(char playerColor)
{
    // Will be returned
    std::vector<std::tuple<int,int,int,int>> legalMoves;

    //Tasks:
    // 1. Go through each square and check if the piece is same color
    // 2. Checking if the piece is valid
    // 3. Checking if the path is clear
    // 4. Checking if the move puts the player in check


    // We grab our piece first, then loop through the board again to check for valid squares to move into
    for (int fromRow=0; fromRow < 8; fromRow++)
    {
        for (int fromCol = 0; fromCol < 8; fromCol++)
        {   auto piece = chessBoard[fromRow][fromCol];
        
            // Finding our pieces
            if (piece != nullptr
            && piece->getPColor() == playerColor)
            {
                char pieceName = toupper(piece->getPName());
                
                // Loop again to find valid squares
                for (int toRow = 0; toRow < 8; toRow++)
                {
                    for (int toCol = 0; toCol <8; toCol++)
                    {
                        // To check if the piece can move into another valid position
                        if(chessBoard[fromRow][fromCol]->isValidMove(toRow, toCol))
                        {
                            bool pathIsClear = true;

                            // The valid position shouldn't be blocked
                            // Horses can jump pieces
                            if (pieceName != 'H')
                            {
                                pathIsClear = isPathClear(fromRow, fromCol, toRow, toCol);
                            }

                            if (pathIsClear)
                            {
                                auto destinationPiece = chessBoard[toRow][toCol];

                                // Specifically checking for pawns, as they can't capture forward, only diagonally
                                // If the column is different after the move
                                if (pieceName == 'P' && destinationPiece==nullptr && fromCol != toCol)
                                {
                                    continue;
                                }
                                
                                // If the pawn is trying to capture the forward square
                                if (pieceName== 'P' && fromCol==toCol && destinationPiece!=nullptr)
                                {
                                    continue;
                                }
                                
                                // Simulating the move to gather the possible moves
                                if (destinationPiece == nullptr
                                    || destinationPiece->getPColor() != playerColor)
                                    {
                                        auto capturedPieceTemp = destinationPiece;

                                        chessBoard[toRow][toCol] = piece;
                                        chessBoard[fromRow][fromCol] = nullptr;

                                        // Check if the move leaves the king safe
                                        if (!isInCheck(playerColor))
                                        {   // Using emplace instead of push because its being bundled here
                                             legalMoves.emplace_back(fromRow,fromCol,toRow,toCol);
                                        }

                                        // Undo the move
                                        chessBoard[fromRow][fromCol] = piece;
                                        chessBoard[toRow][toCol] = capturedPieceTemp;
                                    }
                            }
                        }   
                    }
                }
            }


        }
    }

    return legalMoves;
}

// Promotes the pawn to a piece of the player's choosing
void Board::PawnPromotion(int toRow, int toCol)
{
    auto movedPiece = chessBoard[toRow][toCol];
    if (movedPiece == nullptr || toupper(movedPiece->getPName()) != 'P')
    {
        return;
    }
    

        char promotionChoice = ' ';
        char pieceColor = movedPiece->getPColor();
        int promotionRank = (pieceColor == 'W') ? 0 : 7;

        if (toRow == promotionRank)
        {
            bool validInput = false;
            std::cout << "\nPawn Promotion! Choose piece (Q, R, B, H): ";

            while (!validInput)
            {
                std::cin >> promotionChoice;
                if (promotionChoice == 'Q' || promotionChoice == 'R'
                    || promotionChoice == 'B' || promotionChoice == 'H')
                {
                    validInput = true;
                }

                else
                {
                    std::cout << "Invalid input, please make sure you've entered either Q, R, B or H: ";

                    // Clearing the input buffer since getline only works with chars
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }   // From https://gist.github.com/leimao/418395bf920eb70b2b11fe89d7c1f738

            }


            // Deleting pawn
            delete chessBoard[toRow][toCol];
            chessBoard[toRow][toCol] = nullptr;

            char newPieceName = (pieceColor == 'W') ? promotionChoice : tolower(promotionChoice);


            switch (promotionChoice)
            {
            case 'Q':

                chessBoard[toRow][toCol] = new Queen(toRow, toCol, newPieceName, pieceColor);
                break;

            case 'R':
                chessBoard[toRow][toCol] = new Rook(toRow, toCol, newPieceName, pieceColor);
                break;

            case 'B':
                chessBoard[toRow][toCol] = new Bishop(toRow, toCol, newPieceName, pieceColor);
                break;

            case 'H':
                chessBoard[toRow][toCol] = new Knight(toRow, toCol, newPieceName, pieceColor);
                break;

                std::cout << "Pawn promoted to " << promotionChoice << "!" << std::endl;
            }
        }
}

void Board:: validateStandardMove(int fromRow, int fromCol, int toRow, int toCol)
{
    auto movingPiece = chessBoard[fromRow][fromCol];
    char pieceType = toupper(movingPiece->getPName());

    // Calls the method from the relevant piece class
    if (!movingPiece->isValidMove(toRow, toCol))
    {
        throw "This is not a valid move for this piece";
    }

    // Checking whether the place is occupied by one of the same color
    // First checking whether this place has a piece first as it can cause memory leaks
    if (chessBoard[toRow][toCol] != nullptr
        && chessBoard[toRow][toCol]->getPColor() == chessBoard[fromRow][fromCol]->getPColor())
    {
        throw "You can't capture your own piece";
    }

    // Pawn specific logic

    if (pieceType == 'P')
    {
        int colDiff = abs(toCol-fromCol);

        if (colDiff == 0)
        {
            if (chessBoard[toRow][toCol]!= nullptr)
            {
                throw "Pawns cannot capture moving forward";
            }
            // Checking path for double step
            int rowDiff = abs(toRow - fromRow);
            if (rowDiff == 2)
            {
                if (!isPathClear(fromRow, fromCol, toRow, toCol))
                {
                    throw "Path is blocked for pawn's double step";
                }
            }
        }
        // Diagonal capture
        else if (colDiff == 1)
        {
            if (chessBoard[toRow][toCol] == nullptr)
            {
                throw "Pawns can only move diagonally to capture";
            }
        }

    }

    // checking whether the path is clear
    // Horses won't need this since they can jump
    else if (pieceType != 'H')
    {
        if (!isPathClear(fromRow, fromCol, toRow, toCol))
        {
            throw "Invalid Path";
        }
    }
}

bool Board::isCheckmate(char playerColor)
{   // in check and no legal moves
    if (!isInCheck(playerColor))
    {
        return false;
    }
    return generatePossibleMoves(playerColor).empty();
}

// USED FOR DEBUGGING
//bool Board::isStalemate(char playerColor)
//{
//    if(isInCheck(playerColor))
//    {return false;}
//    auto moves = generatePossibleMoves(playerColor);
//    for (auto const& mv : moves)
//    {
//        int fr, fc, tr, tc;
//        std:: tie(fr,fc,tr,tc) = mv;
//        std::cout << "Debug: move from (" << fr << ',' << fc << ") to (" << tr << ',' << tc << ")\n";
//    }
//    return moves.empty();
//}



 bool Board::isStalemate(char playerColor)
 {   // Not in check but no legal moves
     if (isInCheck(playerColor))
     {
         return false;
     }
     return generatePossibleMoves(playerColor).empty();
 }


bool Board:: isInCheck(char kingColor)
{
    std::pair<int, int> kingPos = findKing(kingColor);
    char attackerColor = (kingColor == 'W') ? 'B' : 'W';


    return (isSquareAttacked(kingPos.first, kingPos.second, attackerColor));
}