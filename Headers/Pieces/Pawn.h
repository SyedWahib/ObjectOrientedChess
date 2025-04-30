#pragma once
# include "Piece.h"

class Pawn : public Piece
{   
    public:

        // This calls the parent class constructor and assigns the values to itself

        Pawn(int row, int col, char name, char color);

        // This will ensure that this method is called when the object is of Pawn type
        bool isValidMove(int newRow, int newCol) override;
};