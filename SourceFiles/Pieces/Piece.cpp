#include "../../Headers/Pieces/Piece.h"
#include <cmath>

int Piece::getRow() const
{
    return row;
}

void Piece::setRow(int newRow)
{
    row = newRow;
}

int Piece::getCol() const
{
    return col;
}

void Piece::setCol(int newCol) 
{
    col = newCol;
}

bool Piece::getFirstMoveState() const
{
    return firstMoveState;
}

void Piece::setFirstMoveState(bool firstMoveState) 
{
    this->firstMoveState = firstMoveState;
}

char Piece::getPName() const
{
    return pName;
}

char Piece::getPColor() const
{
    return pColor;
}
