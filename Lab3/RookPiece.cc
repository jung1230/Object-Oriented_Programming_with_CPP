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
    if (move_row != 0 && move_col != 0) {
        return false; // Not a valid rook move
    }
    // check for if there is a piece blocking the path
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
    // Check the end is the same color or not
    if(_board.getPiece(row, col) == nullptr)
        return true;
    else{
        if(_board.getPiece(row, col)->getColor() == getColor())
            return false;
        else
            return true;
    }
    return true;
}

const char* RookPiece::toString(){
    if(getColor() == Color::Black)
        return ("\u2656");
    else
        return ("\u265c");
}

/**
 * @brief
 * A pure virtual method to be implemented in the derived classes.
 * Determines if movement from current position to new position is valid.
 * This method is for king to check whether it will be captured
 * @param toRow
 * The row of the destination position.
 * @param toColumn
 * The column of the destination position.
 * @return
 * A boolean indicating if the king will be captured, True means it will be captured
 */
bool RookPiece::undercheck(int toRow, int toColumn){
    int move_row = toRow - getRow();
    int move_col = toColumn - getColumn();

    // Rook can only move horizontally or vertically
    if (move_row != 0 && move_col != 0) {
        return false; // Not a valid rook move
    }
    // check for if there is a piece blocking the path
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