#include "../../Headers/Pieces/King.h"
#include <cmath>


King::King (int row, int col, char name, char color) : Piece(row, col, name, color)
{
    firstMoveState = true;
}

bool King::isValidMove(int newRow, int newCol)
{
    int rowDiff = abs(newRow-row);
    int colDiff = abs(newCol-col);

    // Normal move, one space around

    bool normalMove = rowDiff <= 1 && colDiff <= 1 && (rowDiff > 0 || colDiff > 0);

    bool castlingMove = false;

    if (firstMoveState && rowDiff == 0 && colDiff == 2)
    {
        castlingMove = true;
    }

    return normalMove || castlingMove;
}