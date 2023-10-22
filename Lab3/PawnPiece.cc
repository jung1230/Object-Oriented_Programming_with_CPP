#include "PawnPiece.hh"
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
    //A black piece can move in increasing row number (downwards in the figure).
    //A white piece can move in decreasing row number (upwards in the figure).
    if (getColor() == Color::Black){
        // Check whether the pawn can capture the diagnal piece
        if((move_col == 1 || move_col == -1) && (move_row == 1)){
            if(_board.getPiece(getRow() + move_row, getColumn() + move_col) != nullptr){
                if(_board.getPiece(getRow() + move_row, getColumn() + move_col)->getColor() != getColor()){
                    //std::cout << "Capture successfully!" << std::endl;
                    return true;
                }
                else{
                    //std::cout << "Capture falied!" << std::endl;
                    return false;
                }
            }
            else
                return false;
        }
        // can only move forward, two row maximum
        if (move_col != 0 || move_row < 1 || move_row > 2){
            return false;
        }
        // can only move 2 row for the first time
        if (move_row == 2 && getRow() != 1){
            return false; 
        }
        // check if there is piece on path
        for(int i = 1; i <= move_row; i++){
            if (_board.getPiece(getRow() + i, getColumn()) != nullptr) {
                return false; 
            }
        }
    }
    else {
        // Check whether the pawn can capture the diagnal piece
        if((move_col == 1 || move_col == -1) && (move_row == -1)){
            if(_board.getPiece(getRow() + move_row, getColumn() + move_col) != nullptr){
                if(_board.getPiece(getRow() + move_row, getColumn() + move_col)->getColor() != getColor())
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        // can only move forward, two row maximum
        if (move_col != 0 || move_row > -1 || move_row < -2){
            return false;
        }
        // can only move 2 row for the first time
        if (move_row == -2 && getRow() != (_board.getNumRows()-2)){
            return false; 
        }
        // check if there is piece on path
        for(int i = -1; i >= move_row; i--){
            if (_board.getPiece(getRow() + i, getColumn()) != nullptr) {
                return false; 
            }
        }
    }
    return true;
}

const char* PawnPiece::toString()
{
    if (getColor() == Color::White)
        return "\u265F";
    else
        return "\u2659";
}