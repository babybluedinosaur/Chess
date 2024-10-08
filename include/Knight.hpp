#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Piece.hpp"

class Knight : public Piece {
    public:
    Knight(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer);
};

#endif 
