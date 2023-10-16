#include "RookPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */

using Student::RookPiece;

RookPiece::RookPiece(ChessBoard& board, Color color, int row, int column): ChessPiece(board, color, row, column){
            
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
