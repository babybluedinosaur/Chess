#include "include/Board.hpp"
#include "include/Piece.hpp"
#include "include/Pawn.hpp"

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (y==1) board[x][y] = Pawn(false, x, y, nullptr);
        }
    }
}

