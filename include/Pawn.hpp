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
    Pawn(bool color);
    void setColor(bool color);
    void setCoordinates(int x, int y);
    bool getColor();
    void display() const;
};

#endif 
