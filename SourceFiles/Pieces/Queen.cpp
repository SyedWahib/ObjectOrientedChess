#include "../../Headers/Pieces/Queen.h"
#include <cmath>

Queen::Queen(int row, int col, char name, char color) : Piece( row, col, name, color)
{
    firstMoveState = true;
}

bool Queen::isValidMove(int newRow, int newCol)
{
    // Combines both Rook and Bishop

    int rowDiff = abs(newRow - row);
    int colDiff = abs(newCol - col);

    return (rowDiff == colDiff) || (newRow == row || newCol == col);
}
