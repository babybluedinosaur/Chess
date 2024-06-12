#include "King.hpp"

King::King(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer) : 
    Piece(input_color, input_x, input_y, path, renderer) {
}