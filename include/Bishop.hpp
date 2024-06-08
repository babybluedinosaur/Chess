#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "include/Piece.hpp"

class Bishop : public Piece {
    public:
    Bishop(bool input_color, int x, int y,  SDL_Texture* image);
};

#endif 
