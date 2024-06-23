#include "Piece.hpp"


Piece::Piece() {
}

Piece::Piece(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer)
    : white(input_color), x(input_x), y(input_y){
    setImage(path, renderer);
}

void Piece::setImage(std::string path, SDL_Renderer* renderer) {
    path = path;

    //load texture
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

    //place piece on board 
    renderTexture(renderer, image, x, y);
}

void Piece::renderTexture(SDL_Renderer* renderer, SDL_Texture* tex, int x, int y) {
    renderQuad->x = x;
    renderQuad->y = y;
    renderQuad->h = 64;
    renderQuad->w = 64;
    SDL_RenderCopy(renderer, tex, nullptr, renderQuad);
}


void Piece::setCoordinates(int input_x, int input_y) {
    x  = input_x;
    y = input_y;
}

void Piece::setRect(int x, int y) {
    renderQuad->x = x;
    renderQuad->y = y;
}

bool Piece::getColor() const {
    return white;
}

SDL_Texture* Piece::getImage() {
    return image;
}
    
std::pair<int, int> Piece::getCoordinates() {
    return std::make_pair(x, y);
}

SDL_Rect* Piece::getRect() {
    return renderQuad;
}

std::string Piece::getPath() {
    return path;
}


