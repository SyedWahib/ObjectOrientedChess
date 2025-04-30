#pragma once
#include "Piece.h"

class Knight : public Piece
{

    public:

        Knight(int row, int col, char name, char color);

        bool isValidMove(int newRow, int newCol) override;

};