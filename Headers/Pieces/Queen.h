#pragma once
#include "Piece.h"

class Queen : public Piece
{

    public:

        Queen(int row, int col, char name, char color);

        bool isValidMove(int newRow, int newCol) override;
};