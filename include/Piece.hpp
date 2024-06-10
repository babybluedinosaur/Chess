#ifndef PIECE_HPP
#define PIECE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <string>

class Piece {
private:
    bool white;
    int x;
    int y;
    SDL_Texture* image = nullptr;

public:
    Piece();
    Piece(bool input_color, int input_x, int input_y, std::string path, SDL_Renderer* renderer);
    void setImage(std::string path, SDL_Renderer* renderer);
    void setCoordinates(int x, int y);
    bool getColor() const;
    SDL_Texture* getImage();
    std::pair<int, int> getCoordinates();
    SDL_Rect getSDLRect();
};

#endif 
