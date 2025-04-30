#include "../../Headers/Pieces/Knight.h"
#include <cmath>


Knight:: Knight(int row, int col, char name, char color) : Piece(row, col, name, color)
{
    firstMoveState = true;
}

bool Knight::isValidMove(int newRow, int newCol)
{
    // Can only move in L shape
    // But similar to bishop, since it moves two squares in one direction,
    // and the third square in the same row on either side
    // In other words, either 1 row and two columns, or two rows and one column

    int rowDiff = abs(newRow - row);
    int colDiff = abs(newCol-col);

    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

}