#include "../../Headers/Pieces/Bishop.h"
#include <cmath>


Bishop::Bishop(int row, int col, char name, char color) : Piece(row, col, name, color)
{
    firstMoveState = true;
}

bool Bishop::isValidMove(int newRow, int newCol)
{
    //Can only move diagonal, i.e the difference between new and old row and column is same
    int rowDiff = abs(newRow - row);    // absolute since it needs to be positive
    int colDiff = abs(newCol - col);

    return (rowDiff == colDiff);
}

