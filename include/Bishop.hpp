#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Piece.hpp"

class Bishop : public Piece {
    public:
    Bishop(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer);
};

#endif 
