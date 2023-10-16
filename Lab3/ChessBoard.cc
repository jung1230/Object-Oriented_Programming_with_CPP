#include "ChessBoard.hh"
#include "Chess.h"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

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
    // Then, Check whether the piece is at the same place
    // Next, Check the destination is same color
    // Then use piece's canMoveToLocation to check
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

}

