#include "BishopPiece.hh"
#include <iostream>

using Student::BishopPiece;

BishopPiece::BishopPiece(ChessBoard& board, Color color, int row, int column): ChessPiece(board, color, row, column){
            
}

Type BishopPiece::getType(){
    return Type::Bishop;
}

bool BishopPiece::canMoveToLocation(int row, int col){ // Haven't done yet


    std::cout << "12312231" << std::endl;

    int move_row = row - getRow();
    int move_col = col - getColumn();
    if((move_col + move_row != 0) && (move_col - move_row != 0) && (move_row - move_col != 0)){
        std::cout << "32" << std::endl;
        return false;        
    } 

    // Have to check whether there is piece in the moving place
    if((move_row > 0) && (move_col > 0)){
        for(int i = 1; i < move_row; i++){
            for(int j = 1; j < move_col; j++){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr){
                    std::cout << "33" << std::endl;

                    return false;                    
                }

            }
        }
    }
    else if((move_row > 0) && (move_col < 0)){
        for(int i = 1; i < move_row; i++){
            for(int j = -1; j > move_col; j--){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr){
                    std::cout << "34" << std::endl;

                    return false;                    
                }

            }
        }
    }
    else if((move_row < 0) && (move_col > 0)){
        for(int i = -1; i > move_row; i--){
            for(int j = 1; j < move_col; j++){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr){
                    std::cout << "35" << std::endl;

                    return false;                    
                }

            }
        }
    }
    else{
        for(int i = -1; i > move_row; i--){
            for(int j = -1; j > move_col; j--){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr){
                    std::cout << "36" << std::endl;

                    return false;                    
                }

            }
        }
    }
    return true;
}

const char* BishopPiece::toString(){
    if(getColor() == Color::Black)
        return ("U+265D");
    else
        return ("U+2657");
}