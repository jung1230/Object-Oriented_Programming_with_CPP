#include <assert.h>
#include <iostream>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << sBoard.isValidMove(2,3,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

void test_part1_4x4_2(){
    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Rook, 0, 2);
    sBoard.createChessPiece(White, Bishop, 3, 0);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(White, Bishop, 3, 3);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << sBoard.isValidMove(3,3,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

void test_part1_4x4_3(){
    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Bishop, 2, 2);
    sBoard.createChessPiece(White, Rook, 1, 0);
    sBoard.createChessPiece(White, Pawn, 1, 1);
    sBoard.createChessPiece(Black, Pawn, 0, 1);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << sBoard.isValidMove(0,1,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

void test_part1_4x4_5(){
    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Bishop, 0, 1);
    sBoard.createChessPiece(Black, Bishop, 1, 1);
    sBoard.createChessPiece(Black, Bishop, 2, 1);
    sBoard.createChessPiece(White, Pawn, 2, 0);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << sBoard.isValidMove(2,0,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

void test_part1_4x4_7(){
    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Pawn, 2, 2);
    sBoard.createChessPiece(Black, Rook, 3, 2);
    sBoard.createChessPiece(White, Pawn, 3, 1);
    sBoard.createChessPiece(Black, Pawn, 1, 0);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << sBoard.isValidMove(3,2,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

void test_part1_6x6_2(){
    // Corresponding code
    Student::ChessBoard sBoard(6, 6);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(White, Bishop, 1, 1);
    sBoard.createChessPiece(White, Bishop, 0, 0);
    sBoard.createChessPiece(White, Rook, 1, 4);
    sBoard.createChessPiece(White, Pawn, 3, 3);
    sBoard.createChessPiece(Black, Pawn, 2, 1);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            std::cout << sBoard.isValidMove(2,1,i,j) << " ";
        }
        std::cout << std::endl;
    }

    return;
}

// ------------------------------ chessboard ------------------------------
void unit_isValidMove_bishop_one() {
	Student::ChessBoard board(4, 4);
	board.createChessPiece(White, Bishop, 0, 0);
	

	assert(board.isValidMove(0, 0, 3, 3));
	assert(!board.isValidMove(0, 0, 1, 2));
	assert(!board.isValidMove(0, 0, -1, -1));
}
void unit_isValidMove_Rook() {
	Student::ChessBoard board(4, 4);
	board.createChessPiece(White, Rook, 0, 0);
	

	assert(board.isValidMove(0, 0, 3, 0));
    assert(board.isValidMove(0, 0, 0, 3));
    assert(!board.isValidMove(0, 0, 3, 3));
	assert(!board.isValidMove(0, 0, 1, 2));
	assert(!board.isValidMove(0, 0, -1, -1));
}

void unit_isValidMove_Pawn() {
	Student::ChessBoard board(4, 4);
	board.createChessPiece(White, Pawn, 0, 0);
	

	assert(board.isValidMove(0, 0, 2, 0));
    assert(board.isValidMove(0, 0, 1, 0));
    assert(!board.isValidMove(0, 0, 0, 1));
	assert(!board.isValidMove(0, 0, 1, 2));
	assert(!board.isValidMove(0, 0, -1, -1));
}


int main()
{
    //unit_isValidMove_bishop_one();
    //unit_isValidMove_Rook();
    //unit_isValidMove_Pawn();
    //test_part1_4x4_1();
    test_part1_4x4_5();
    return EXIT_SUCCESS;
}
