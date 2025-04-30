#pragma once

class Piece
{
    protected:

        int row;
        int col;
        bool firstMoveState; // True if piece hasn't moved, False if it has
                             // Should be useful for implementing special moves like Pawn's first two moves and castling etc...
        char pName;
        char pColor;

        Piece(int row, int col, char pName, char pColor)
        : row(row), col (col) , firstMoveState(true), pName(pName), pColor(pColor)
        {}

    public:

        int getRow() const;

        void setRow(int newRow);

        int getCol() const;

        void setCol(int newCol);

        bool getFirstMoveState() const;

        void setFirstMoveState(bool firstMoveState);
        char getPName() const;

        char getPColor() const;

        // This will be piece specific, called according to the piece's implementation of this method
        virtual bool isValidMove(int newRow, int newCol) = 0;
        virtual ~Piece() {}
};