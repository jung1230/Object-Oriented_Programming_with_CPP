#include "BishopPiece.hh"
#include <iostream>

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
    if(getColor() == Color::Black)
        return ("\u265D");
    else
        return ("\u2657");
}