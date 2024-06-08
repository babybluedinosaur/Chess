#ifndef PAWN_HPP
#define PAWN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "include/Piece.hpp"

class King : public Piece {
    public:
    King(bool input_color, int x, int y,  SDL_Texture* image);
};

#endif 
