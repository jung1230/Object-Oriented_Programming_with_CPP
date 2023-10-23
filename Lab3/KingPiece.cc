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
        return false; // Not a valid rook move
    }
 
    // if target is not null or it is not an opponent, return false
    ChessPiece* target = _board.getPiece(row, col);
    if ((target == nullptr || target -> getColor() != getColor()) == 0)
        return false;
    
    // Check if the move puts itself in check by creating a copy of the board to simulate it
    ChessBoard temp = _board; 
    temp.movePiece(getRow(), getColumn(), row, col);
    // if king is moving to place that will make him under threat, return false
    if (temp.isPieceUnderThreat(row, col)) {
        return false;  
    }

    return true;
}

const char* KingPiece::toString(){
    if(getColor() == Color::Black)
        return ("\u2656");
    else
        return ("\u265c");
}
