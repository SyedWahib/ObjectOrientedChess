#include "../../Headers/Pieces/Rook.h"
#include <cmath>

Rook::Rook(int row, int col, char name, char color) : Piece(row, col, name, color)
{
    firstMoveState = true;
}

bool Rook::isValidMove(int newRow, int newCol)
{
    // Rook = Horizontal + Vertical

    return (newRow == row || newCol == col);

}