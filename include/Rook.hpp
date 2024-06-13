#ifndef ROOK_HPP
#define ROOK_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Piece.hpp"

class Rook : public Piece {
    public:
    Rook(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer);
};

#endif 
