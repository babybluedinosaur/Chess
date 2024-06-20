#include "Board.hpp"

Board::Board() {
    initializeSDL();

    bool quit = false;
    while (!quit) {
        handleEvents(quit);
        buildBoard(window, renderer);
    }
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            delete board[x][y];
            board[x][y] = nullptr;
        }
    }
    closeSDL();
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
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            //black
            if (y == 0) {
                if(x == 0) board[x][y] = new Rook(false, 80*x+5, 5,"black/black_rook.png", renderer);
                if(x == 1) board[x][y] = new Knight(false, 80*x+5, 5,"black/black_knight.png", renderer);
                if(x == 2) board[x][y] = new Bishop(false, 80*x+5, 5,"black/black_bishop.png", renderer);
                if(x == 3) board[x][y] = new Queen(false, 80*x+5, 5,"black/black_queen.png", renderer);
                if(x == 4) board[x][y] = new King(false, 80*x+5, 5,"black/black_king.png", renderer);
                if(x == 5) board[x][y] = new Bishop(false, 80*x+5, 5,"black/black_bishop.png", renderer);
                if(x == 6) board[x][y] = new Knight(false, 80*x+5, 5,"black/black_knight.png", renderer);
                if(x == 7) board[x][y] = new Rook(false, 80*x+5, 5,"black/black_rook.png", renderer);

            } else if (y == 1) board[x][y] = new Pawn(false, 80*x+5, 80,"black/black_pawn.png", renderer);
            //white
            else if (y == 6) board[x][y] = new Pawn(true, 80*x+5, 480,"white/white_pawn.png", renderer);
            else if (y == 7) {
                if(x == 0) board[x][y] = new Rook(true, 80*x+5, 565,"white/white_rook.png", renderer);
                if(x == 1) board[x][y] = new Knight(true, 80*x+5, 565,"white/white_knight.png", renderer);
                if(x == 2) board[x][y] = new Bishop(true, 80*x+5, 565,"white/white_bishop.png", renderer);
                if(x == 3) board[x][y] = new Queen(true, 80*x+5, 565,"white/white_queen.png", renderer);
                if(x == 4) board[x][y] = new King(true, 80*x+5, 565,"white/white_king.png", renderer);
                if(x == 5) board[x][y] = new Bishop(true, 80*x+5, 565,"white/white_bishop.png", renderer);
                if(x == 6) board[x][y] = new Knight(true, 80*x+5, 565,"white/white_knight.png", renderer);
                if(x == 7) board[x][y] = new Rook(true, 80*x+5, 565,"white/white_rook.png", renderer);
            } else board[x][y] = nullptr;
        }
    }
    SDL_RenderPresent(renderer);

}

double bankers_round(double value) {
    std::fesetround(FE_TONEAREST);
    return std::nearbyint(value);
}

void Board::handleEvents(bool& quit) {
    SDL_Event event;
    int mouseX, mouseY;
    int offsetX, offsetY;
    bool isPickedUp = false;
    Piece* selectedObject = nullptr;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                
                //normalize mouse posiiton
                mouseX = event.button.x;
                mouseY = event.button.y;
                int x = (event.button.y-5)/80;
                int y = (event.button.x-5)/80;
                x = bankers_round(x);
                y = bankers_round(y);
               
                //get piece nearest to mouse position
                Piece* piece = board[x][y];
                if (piece != nullptr) {

                    //calculate array coordinates of piece
                    std::pair piecePos = piece->getCoordinates();       
                    int pieceX = (piecePos.first-5)/80;
                    int pieceY = (piecePos.second)/80;

                    if (!isPickedUp && mouseX >= piecePos.first && mouseX <= piecePos.first + 64 &&
                        mouseY >= piecePos.second && mouseY <= piecePos.second + 64) {
        
                        isPickedUp = true;
                        offsetX = mouseX - piecePos.first;
                        offsetY = mouseY - piecePos.second;
                        
                    } else if (isPickedUp) {

                        // Place the piece
                        SDL_Rect* pieceRect = board[pieceX][pieceY]->getRect(); 
                        pieceRect->x = mouseX - offsetX;
                        pieceRect->y = mouseY - offsetY;
                        isPickedUp = false;
                    }
                }
            }
        }
    }
}


int main(int argc, char* argv[]) {
    Board bruh = Board();
    return 0;
}

