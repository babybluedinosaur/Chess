#include "include/Board.hpp"

Board::Board() {
    initializeSDL();
    initializeBoard();

    bool quit = false;
    while (!quit) {
        handleEvents(quit);
        buildBoard(window, renderer);
    }

    closeSDL();
    buildBoard(window, renderer);
}

void Board::initializeBoard() {
    Pawn(false, 1, 1,"/home/sidar/Downloads/white_pawn.png", renderer);    
}

bool Board::initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL GUI Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Board::closeSDL() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void Board::buildBoard(SDL_Window* window, SDL_Renderer* renderer) {
    font = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 22);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b, GRID_COLOR.a);
    for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    int foo = 8;
    int bruh = 0;

    for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
        for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
            SDL_Rect fieldRect = { x, y, GRID_SIZE, GRID_SIZE };
            SDL_Color fillColor;
            SDL_Color textColor;
            if (((x / GRID_SIZE) + (y / GRID_SIZE)) % 2 == 0) {
                fillColor = FIELD_COLOR;
                textColor = ALT_FIELD_COLOR;
            } else {
                fillColor = ALT_FIELD_COLOR;
                textColor = FIELD_COLOR;
            }
            SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
            SDL_RenderFillRect(renderer, &fieldRect);

            if (x == 0) {
                std::string text = std::to_string(foo);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                int indexX = x + GRID_SIZE - 80;
                int indexY = y + GRID_SIZE - 80;
                SDL_Rect textRect = { indexX, indexY, textSurface->w, textSurface->h };
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
                foo--;
            }

            const char* chars[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
            if (y == WINDOW_HEIGHT - GRID_SIZE) {
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, chars[bruh], textColor);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                int indexX = x + GRID_SIZE - 20;
                int indexY = y + GRID_SIZE - 25;
                SDL_Rect textRect = { indexX, indexY, textSurface->w, textSurface->h };
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
                bruh++;
            }
        }
    }

    Pawn huh = Pawn(true, 100, 100,"/home/sidar/Downloads/white_pawn.png", renderer);    
    SDL_RenderPresent(renderer);
}

void Board::handleEvents(bool& quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

int main(int argc, char* argv[]) {
    Board bruh = Board();
    return 0;
}

