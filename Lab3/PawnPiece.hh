#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
        private:
            int move_count = 0;
        public:
            PawnPiece(ChessBoard& board, Color color, int row, int column);
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char* toString() override;
            bool undercheck(int toRow, int toColumn) override;
    };
}

#endif


