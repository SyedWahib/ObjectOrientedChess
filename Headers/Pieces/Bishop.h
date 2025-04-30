#pragma once
#include "Piece.h"

class Bishop : public Piece
{

    public:

        Bishop(int row, int col, char name, char color);

        bool isValidMove(int newRow, int newCol) override;
};