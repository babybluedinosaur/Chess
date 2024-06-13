#ifndef KING_HPP
#define KING_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Piece.hpp"

class King : public Piece {
    public:
    King(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer);
};

#endif 
