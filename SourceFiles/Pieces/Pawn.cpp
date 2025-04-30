#include "../../Headers/Pieces/Pawn.h"
#include <cmath>


// This calls the parent class constructor and assigns the values to itself

        Pawn::Pawn(int row, int col, char name, char color): Piece(row, col, name, color)
        {
            firstMoveState = true;
        }

        // This will ensure that this method is called when the object is of Pawn type
        bool Pawn::isValidMove(int newRow, int newCol)

        
        {   // Pawns are the only piece to only move in one direction, so we need to initialize direction depending on color
            int direction = (pColor == 'B') ? 1 : -1;

            int rowDiff = newRow - row;
            int colDiff = abs(newCol - col);

            // There are 5 types of pawn moves possible, promotion will be handled in the board class
            // and en passant is not a part of this project for the time being

            // 1) Moving forward with no capture
            if (colDiff==0)
            {
                if(rowDiff == direction)
                {
                    return true;
                }
            
            // 2) Moving forward 2 spaces if firstMoveState == true

            // If firstMoveState is true and difference between old/new rows is equal to 2 for black or -2 for white
                
                else if (firstMoveState && rowDiff == 2* direction)
                {
                    return true;
                }


            }

            // 3) Moving diagonally forward if capture available

            else if (colDiff == 1 && rowDiff == direction)
            {
                return true;
            }


            return false;

        }




