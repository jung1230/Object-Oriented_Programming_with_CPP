#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    ChessPiece::ChessPiece(ChessBoard& board, Color color, int row, int column): _board(board), _color(color), _row(row), _column(column){

    }

    Type RookPiece::getType(){
        return Type::Rook;
    }

    bool RookPiece::canMoveToLocation(int row, int col){
        int move_row = row - getRow();
        int move_col = col - getColumn();

        // Rook can only move horizontally or vertically
        return (move_row == 0 && move_col != 0) || (move_row != 0 && move_col == 0);
    }

    const char* RookPiece::toString(){
        return ("U+265C");
    }
}

#endif
