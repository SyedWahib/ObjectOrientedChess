#pragma once
#include <array>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <fstream>
#include "../Pieces/Piece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/King.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Knight.h"

class Board
{
    private:
    std::array <std::array <Piece*, 8>, 8> chessBoard;
    bool isWhiteTurn = true;
    std::string fromPosition;
    std::string toPosition;
    int newRow;
    int newCol;
    const std:: string letters = "abcdefgh";

    std:: string convertToNotation(int row, int col);

    void convertFromNotation(std:: string notation);

    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);

    std::pair<int, int> findKing(char kingColor);

    bool isSquareAttacked(int row, int col, char attackerColor);

    bool isInCheck(char kingColor);

    //Will generate the legal moves for the player
    // Returns a vector of tuples of the form (fromRow, fromCol, toRow, toCol)
    std:: vector<std::tuple<int,int,int,int>> generatePossibleMoves(char playerColor);

    // If in check and the above method returns an empty list, its checkmate
    bool isCheckmate(char playerColor);

    // Must not be in check and no possible moves
    bool isStalemate(char playerColor);

    void resetBoard(std:: array<std:: array<Piece*, 8>, 8>& chessBoard);

    void placePieces(std:: array <std::array<Piece*, 8>,8>& chessBoard);
    
    void setBoard(std:: array<std:: array<Piece*, 8>, 8>& chessBoard);

    // Generates String to be displayed and/or saved
    std::string displayBoardToString();

    //Functionality for saving the game
    void saveGame();

    void saveGameResult (std:: string result);

    void PawnPromotion(int toRow, int toCol);
        
    // Exception when invalid move
    void validateStandardMove(int fromRow, int fromCol, int toRow, int toCol);

    public:


        Board();

        ~Board();

        void displayBoard();

        //Changed to bool so that main can use this, true = game is alive, false = game is over
        bool movePiece();


};
