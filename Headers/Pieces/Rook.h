#pragma once
#include "Piece.h"

class Rook : public Piece
{

    public:
        Rook(int row, int col, char name, char color);

        bool isValidMove(int newRow, int newCol) override;
};