#include "Piece.hpp"


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
    renderQuad->x = x;
    renderQuad->y = y;
    renderQuad->h = 64;
    renderQuad->w = 64;
    SDL_RenderCopy(renderer, image, nullptr, renderQuad);
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


// int main() {
//     SDL_Window* window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
// SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// Piece testPiece(false, 100, 100, "/home/sidar/Downloads/white_pawn.png", renderer);

// SDL_RenderPresent(renderer);

// SDL_Delay(2000);

// SDL_DestroyRenderer(renderer);
// SDL_DestroyWindow(window);

// }
