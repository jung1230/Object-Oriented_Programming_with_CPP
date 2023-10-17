#include "PawnPiece.hh"
#include <iostream>
using Student::PawnPiece;

PawnPiece::PawnPiece(ChessBoard& board, Color color, int row, int column): ChessPiece(board, color, row, column){
}

Type PawnPiece::getType()
{
    return Type::Pawn;
}

bool PawnPiece::canMoveToLocation(int row, int col)
{
    int move_row = row - getRow();
    int move_col = col - getColumn();

    if (getColor() == Color::White){
        // can only move forward, two row maximum
        if (move_col != 0 || move_row < 1 || move_row > 2){
            return false;
        }
        // can only move 2 row for the first time
        if (move_row == 2 && move_count != 0){

            return false; 
        }
    }
    else {
        // can only move forward, two row maximum
        if (move_col != 0 || move_row > -1 || move_row < -2){
            return false;
        }
        // can only move 2 row for the first time
        if (move_row == -2 && move_count != 0){
            return false; 
        }
    }

    // check if there is piece on path
    if (move_row > 0) {
        for (int i = 1; i < move_row; i++) {
            if (_board.getPiece(getRow() + i, getColumn()) != nullptr) {
                return false; 
            }
        }
    } 
    else if (move_row < 0) {
        for (int i = -1; i > move_row; i--) {
            if (_board.getPiece(getRow() + i, getColumn()) != nullptr) {
                return false; 
            }
        }
    } 
    else if (move_col > 0) {
        for (int i = 1; i < move_col; i++) {
            if (_board.getPiece(getRow(), getColumn() + i) != nullptr) {
                return false; 
            }
        }
    } 
    else if (move_col < 0) {
        for (int i = -1; i > move_col; i--) {
            if (_board.getPiece(getRow(), getColumn() + i) != nullptr) {
                return false; 
            }
        }
    }

    return true;
}

const char* PawnPiece::toString()
{
    if (getColor() == Color::Black)
        return "\u265F";
    else
        return "\u2659";
}
