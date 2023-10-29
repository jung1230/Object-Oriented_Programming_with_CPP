#include "ChessBoard.hh"
#include "Chess.h"
#include "vector"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
//#include <iostream>

using Student::ChessBoard;

/**
 * @brief
 * Allocates memory on the heap for the board.
 * Remember to initialise all pointers to nullptr.
 * @param numRow
 * Number of rows of the chess board.
 * @param numCol
 * Number of columns of the chessboard
 */
ChessBoard::ChessBoard(int numRow, int numCol){
    numRows = numRow;
    numCols = numCol;
    for(int i = 0; i < numRow; i++){
        board.push_back(std::vector<ChessPiece *>(numCol));
        for(int j = 0; j < numCol; j++){
            board.at(i).at(j) = nullptr;
        }
    }
}

/**
 * @brief
 * Returns an output string stream displaying the layout of the board.
 * An ostringstream is used to automatically handle formatting of integers
 * and special characters into their string representations.
 * @return
 * An output stream containing the full board layout.
 */
std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}

/**
 * @brief
 * Checks if a move is valid without accounting for turns.
 * @param fromRow
 * The row of the piece to be moved.
 * @param fromColumn
 * The column of the piece to be moved.
 * @param toRow
 * The row of the destination position.
 * @param toColumn
 * The column of the destination position.
 * @return
 * Returns true if move may be executed without accounting for turn.
 */
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn){
    // First, Check whether it is in the bound
    if((fromRow < 0) || (fromColumn < 0) || (toRow < 0) || (toColumn < 0)){
        return false;

    }
    if((fromRow >= numRows) || (toRow >= numRows) || (fromColumn >= numCols) || (toColumn >= numCols)){
       return false;

    }
    // Then Check whether there is a piece at the fromRow and fromColumn
    if(board.at(fromRow).at(fromColumn) == nullptr){
       return false;
    }
    // Then, Check whether the piece is at the same place
    if((fromRow == toRow) && (fromColumn == toColumn)){
       return false;

    }
    // Then Check the piece moved is the right color
    // Don't need to account for turn in part 1
    /*if(board.at(fromRow).at(fromColumn)->getColor() != turn){
        return false;

    }*/
    // Next, Check the destination is same color
    /*if(board.at(toRow).at(toColumn) != nullptr){
        if(board.at(toRow).at(toColumn)->getColor() == turn){
            return false;
        }
    }*/
    // Then use piece's canMoveToLocation to check
    if(board.at(fromRow).at(fromColumn)->canMoveToLocation(toRow, toColumn)){
        return true;

    }
    else{
        return false;
    }
        
}

/**
         * @brief
         * Allocates memory for a new chess piece and assigns its
         * address to the corresponding pointer in the 'board' variable.
         * Remove any existing piece first before adding the new piece.
         * @param col
         * Color of the piece to be created.
         * @param ty
         * Type of the piece to be created.
         * @param startRow
         * Starting row of the piece to be created.
         * @param startColumn
         * Starting column of the piece to be created.
         */
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn){
    //  Remove any existing piece first before adding the new piece.
    ChessPiece* existing_piece = getPiece(startRow, startColumn);
    if (existing_piece != nullptr) {
        delete existing_piece; // Delete the existing piece
    }

    // adding new piece with its type
    ChessPiece* new_piece = nullptr;
    if (ty == Pawn) { 
        new_piece = new PawnPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Bishop) { 
        new_piece = new BishopPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Rook) { 
        new_piece = new RookPiece(*this, col, startRow, startColumn);
    }
    else if (ty == King) {
        new_piece = new KingPiece(*this, col, startRow, startColumn);
    }

    // Put the new piece on the board
    board[startRow][startColumn] = new_piece;
}


// Alan Part 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool ChessBoard::isPieceUnderThreat(int row, int col) {
    /**
    * @brief
    * Checks if the piece at a position is under threat.
    * @param row
    * Row of piece being checked.
    * @param column
    * Column of piece being checked.
    * @return
    * Returns true if a piece exists at the stated position, and an opponent
    * piece may move to the position.
    */

    // check if there is a piece a that specific location
    ChessPiece* CheckPiece = getPiece(row, col);

    // it can't be threaten if there is no piece 
    if (CheckPiece == nullptr) {
        return false;
    }

    // iterate through all piece, and check if there is a piece with different color that can move to that location
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            ChessPiece* piece = board.at(i).at(j);

            //if there is no piece there, or it is same color as checkpiece, continue the loop
            if (piece == nullptr){
                continue;
            }
            if(piece -> getColor() == CheckPiece -> getColor())
                continue;
            // if oponent can move to checkpiece's location, checkpiece is under threaten
            if (piece -> canMoveToLocation(row, col)){
                return true;
            }

        }
    }




    return false;
}




// Part 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    if(!isValidMove(fromRow, fromColumn, toRow, toColumn)){
        return false;
    }
        
    // Check whether it is the right turn for the piece to move
    if(board.at(fromRow).at(fromColumn)->getColor() != turn){
        return false;
    }

    // Move the piece, temp maybe captured
    ChessPiece *temp = board.at(toRow).at(toColumn);
    board.at(toRow).at(toColumn) = board.at(fromRow).at(fromColumn);
    board.at(fromRow).at(fromColumn) = nullptr;
    board.at(toRow).at(toColumn)->setPosition(toRow, toColumn);



    // ------------------------------part 3-----------------------------
    for(int i = 0; i < board.getRow(); i++){
        for(int j = 0; j < board.getCol(); j++){
            if(board.at(i).at(j).getType == Type::King && board.at(i).at(j).getColor() == getColor()){
                if(board.isPieceUnderThreat(i,j)){
                    board.at(fromRow).at(fromColumn) = board.at(toRow).at(toColumn);
                    board.at(fromRow).at(fromColumn)->setPosition(fromRow, fromColumn);  
                    board.at(toRow).at(toColumn) = temp;  
                    return false;       
                }
            }
        }
    }
    // capture the chesspiece if it is not a nullptr 
    if(temp != nullptr){
        delete temp;
    }

    //Change the turn
    if(turn == Color::White)
        turn = Color::Black;
    else
        turn = Color::White;
    return true;
}

ChessBoard::~ChessBoard(){
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(board.at(i).at(j) != nullptr)
                delete board.at(i).at(j);
        }
    }
}