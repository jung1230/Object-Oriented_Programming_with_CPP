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
    if((move_col+move_row != 0) || (move_col-move_row != 0) || (move_row-move_col != 0)) // Not moving like a bishop
        return false;
    // Have to check whether there is piece in the moving place
    if((move_row > 0) && (move_col > 0)){
        for(int i = 1; i < move_row; i++){
            for(int j = 1; j < move_col; j++){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr)
                    return false;
            }
        }
    }
    else if((move_row > 0) && (move_col < 0)){
        for(int i = 1; i < move_row; i++){
            for(int j = -1; j > move_col; j--){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr)
                    return false;
            }
        }
    }
    else if((move_row < 0) && (move_col > 0)){
        for(int i = -1; i > move_row; i--){
            for(int j = 1; j < move_col; j++){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr)
                    return false;
            }
        }
    }
    else{
        for(int i = -1; i > move_row; i--){
            for(int j = -1; j > move_col; j--){
                if(_board.getPiece(getRow() + i, getColumn() + j) != nullptr)
                    return false;
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