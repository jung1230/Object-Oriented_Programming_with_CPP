#include "Chess.h"
#include "ChessPiece.hh"

using Student::ChessPiece;

/**
  * @brief
  * Constructor for ChessPiece.
  * @param board
  * The board to which the piece belongs.
  * @param color
  * The colour of the piece.
  * @param row
  * Starting row of the piece.
  * @param column
  * Starting column of the piece.
  */

// Alan
ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column): _board(board), _color(color), _row(row), _column(column){

}

/**
  * @brief
  * Default destructor for ChessPiece.
  * Does nothing special.
  */
//virtual ~ChessPiece() {}

/**
  * @return
  * Colour of piece.
  */
Color ChessPiece::getColor(){
  return _color;
}

/**
  * @return
  * Type of piece.
  *
  * Note: An alternate perhaps more ideal way of implementation
  * would have been to define this function as pure virtual and
  * let each derived class override this function.
  */

// Alan
// Type ChessPiece::getType(){
  // I changed this into pure virtual function, remember to declare this for every derived function
// }

/**
  * @return
  * Current row number of piece.
  */
int ChessPiece::getRow(){
  return _row;
}

/**
  * @return
  * Current column number of piece.
  */

// Alan
int ChessPiece::getColumn(){
  return _column;
}

/**
  * @brief Sets row and column numbers of piece.
  * @param row
  * The new row number of the piece.
  * @param column
  * The new column number of the piece.
  */
void ChessPiece::setPosition(int row, int column){
  _row = row;
  _column = column;
}

/**
  * @brief
  * A pure virtual method to be implemented in the derived classes.
  * Determines if movement from current position to new position is valid.
  * @param toRow
  * The row of the destination position.
  * @param toColumn
  * The column of the destination position.
  * @return
  * A boolean indicating if a move from current to destination is valid.
  */

// Alan
// this is a pure virtul function
//virtual bool canMoveToLocation(int toRow, int toColumn) = 0;

/**
  * @brief
  * A pure virtual method to be implemented in the derived classes.
  * Returns a unicode string representation of the piece.
  * Refer to this link https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
  * for more information on unicode representation of chess piece.
  * @return
  * A unicode representation of the piece.
  */
//virtual const char *toString() = 0;
