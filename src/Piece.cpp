#include "include/Piece.hpp"

Piece::Piece(bool input_color, int input_x, int input_y, SDL_Texture* image)
    :white(input_color), x(input_x), y(input_y), image(image) {
    
}

void Piece::setCoordinates(int input_x, int input_y) {
    x  = input_x;
    y = input_y;
}

bool Piece::getColor() const {
    return white;
}
    
std::pair<int, int> Piece::getCoordinates() {
    return std::make_pair(x, y);
}

void Piece::display() const {

}