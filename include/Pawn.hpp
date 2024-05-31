#ifndef PAWN_HPP
#define PAWN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <string>

class Pawn {
private:
    bool white;
    int x;
    int y;
    SDL_Texture* image;

public:
    Pawn(bool input_color, int input_x, int input_y, SDL_Texture* image);
    void setCoordinates(int x, int y);
    bool getColor() const;
    std::pair<int, int> getCoordinates();
    void display() const;
};

#endif 
