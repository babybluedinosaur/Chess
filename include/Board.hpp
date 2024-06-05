#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Piece.hpp"
#include <string>

class Board {
private:
    Piece board[8][8];

public:
    Board();
    void initializeBoard();
    void display() const;
};

#endif 
