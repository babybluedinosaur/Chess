#include "include/Piece.hpp"


Piece::Piece() {
}

Piece::Piece(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer)
    : white(input_color), x(input_x), y(input_y){
    setImage(path, renderer);
}

void Piece::setImage(std::string path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image" << std::endl;
    } else {
        image = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (image == nullptr) {
            std::cerr << "Unable to create texture" << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    SDL_Rect renderQuad = { x, y, 64, 64 };
    SDL_RenderCopy(renderer, image, nullptr, &renderQuad);
    SDL_RenderPresent(renderer);
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