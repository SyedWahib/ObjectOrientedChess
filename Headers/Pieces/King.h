#pragma once
#include "Piece.h"

class King : public Piece
{

    public:

        King (int row, int col, char name, char color);

        bool isValidMove(int newRow, int newCol) override;
};