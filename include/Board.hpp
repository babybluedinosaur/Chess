#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <cfenv>

using namespace std;

#pragma STDC FENV_ACCESS ON

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Knight.hpp"

class Board {
private:
    Piece* board[8][8];
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 640;
    const int GRID_SIZE = 80; 
    const SDL_Color GRID_COLOR = { 100, 100, 100, 255 };
    const SDL_Color FIELD_COLOR = { 50, 50, 50, 50 };
    const SDL_Color ALT_FIELD_COLOR = { 255, 255, 245, 0 };

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool isPickedUp = false;
    int offsetX, offsetY = 0;
    Piece* selectedPiece = nullptr;

public:
    Board();
    void initializeBoard();
    void buildBoard(SDL_Window* window, SDL_Renderer* renderer);
    void handleEvents(bool& quit);
    bool initializeSDL();
    void closeSDL();
    void display() const;

};

#endif 
