#include "KingPiece.hh"


using Student::KingPiece;

KingPiece::KingPiece(ChessBoard& board, Color color, int row, int column) : ChessPiece(board, color, row, column){
            
}


Type KingPiece::getType(){
    return Type::King;
}

bool KingPiece::canMoveToLocation(int row, int col){
    int move_row = row - getRow();
    int move_col = col - getColumn();

    // king can only move around him
    if (move_row > 1 || move_row < -1 || move_col > 1 || move_col < -1) {
        return false;
    }
 
    // if target is not null and it is not an opponent or it is a king, return false
    ChessPiece* target = _board.getPiece(row, col);
    if(target != nullptr){
        if((target->getColor() == getColor()))
            return false;
    }
    // Check if the move puts itself in check by creating a copy of the board to simulate it
    /*ChessBoard temp = _board; 
    temp.movePiece(getRow(), getColumn(), row, col);
    // if king is moving to place that will make him under threat, return false
    if (temp.isPieceUnderThreat(row, col)) {
        return false;  
    }*/
    int numrow = _board.getNumRows();
    int numcol = _board.getNumCols();
    //ChessPiece *temp = _board.getPiece(row,col);
    

    for (int i = 0; i < numrow; i++) {
        for (int j = 0; j < numcol; j++) {
            if((i == row)&&(j==col)){
                continue;
            }
            ChessPiece* piece = _board.getPiece(i, j);
            //if there is no piece there, or it is same color as checkpiece, continue the loop
            if (piece == nullptr){
                continue;
            }
            if(piece -> getColor() == getColor())
                continue;
            /*if(piece -> getType() == getType())
                continue;*/
            // if oponent can move to checkpiece's location, checkpiece is under threaten
            // if (piece -> undercheck(row, col)){
            //     return false;
            // }
        }
    }

    return true;
}

const char* KingPiece::toString(){
    if(getColor() == Color::Black)
        return ("\u265A");
    else
        return ("\u2654");
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
// dummy operation of undercheck method in KingPiece
bool KingPiece::undercheck(int toRow, int toColumn){
    return false;
}
