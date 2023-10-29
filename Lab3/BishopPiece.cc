#include "BishopPiece.hh"

using Student::BishopPiece;

BishopPiece::BishopPiece(ChessBoard& board, Color color, int row, int column): ChessPiece(board, color, row, column){
            
}

Type BishopPiece::getType(){
    return Type::Bishop;
}

bool BishopPiece::canMoveToLocation(int row, int col){ // Haven't done yet



    int move_row = row - getRow();
    int move_col = col - getColumn();
    if((move_col + move_row != 0) && (move_col - move_row != 0) && (move_row - move_col != 0)){
        return false;        
    } 

    // Have to check whether there is piece in the moving place
    if((move_row > 0) && (move_col > 0)){
        for(int i = 1; i < move_row; i++){
            if(_board.getPiece(getRow() + i, getColumn() + i) != nullptr){
                return false;                    
            }
        }
    }
    else if((move_row > 0) && (move_col < 0)){
        for(int i = 1; i < move_row; i++){
            if(_board.getPiece(getRow() + i, getColumn() - i) != nullptr){
                return false;                    
            }
        }
    }
    else if((move_row < 0) && (move_col > 0)){
        for(int i = -1; i > move_row; i--){
            if(_board.getPiece(getRow() + i, getColumn() - i) != nullptr){
                return false;                    
            }
        }
    }
    else{
        for(int i = -1; i > move_row; i--){
            if(_board.getPiece(getRow() + i, getColumn() + i) != nullptr){
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

const char* BishopPiece::toString(){
    if(getColor() == Color::White)
        return ("\u2657");
    else
        return ("\u265D");
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
bool BishopPiece::undercheck(int toRow, int toColumn){
    int move_row = toRow - getRow();
    int move_col = toColumn - getColumn();
    if((move_col + move_row != 0) && (move_col - move_row != 0) && (move_row - move_col != 0)){
        return false;        
    } 

    // Have to check whether there is piece in the moving place
    if((move_row > 0) && (move_col > 0)){
        for(int i = 1; i < move_row; i++){
            if(_board.getPiece(getRow() + i, getColumn() + i) != nullptr){
                return false;                    
            }
        }
    }
    else if((move_row > 0) && (move_col < 0)){
        for(int i = 1; i < move_row; i++){
            if(_board.getPiece(getRow() + i, getColumn() - i) != nullptr){
                return false;                    
            }
        }
    }
    else if((move_row < 0) && (move_col > 0)){
        for(int i = -1; i > move_row; i--){
            if(_board.getPiece(getRow() + i, getColumn() - i) != nullptr){
                return false;                    
            }
        }
    }
    else{
        for(int i = -1; i > move_row; i--){
            if(_board.getPiece(getRow() + i, getColumn() + i) != nullptr){
                return false;                    
            }
        }
    }
    return true;
}