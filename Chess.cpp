#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
const int GRID_SIZE = 80; 
const SDL_Color GRID_COLOR = { 100, 100, 100, 255 }; // Adjust the grid color
const SDL_Color FIELD_COLOR = { 0, 0, 0, 0 }; // Adjust the color of the field
const SDL_Color ALT_FIELD_COLOR = { 255, 255, 255, 0 }; // Adjust the color of the alternate field

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL GUI Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the font
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Event loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw grid
        SDL_SetRenderDrawColor(renderer, GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b, GRID_COLOR.a);
        for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT); // Vertical lines
        }
        for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y); // Horizontal lines
        }

        int foo = 1;

        // Render text in each grid cell
        for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
            for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
                SDL_Rect fieldRect = { x, y, GRID_SIZE, GRID_SIZE };
                SDL_Color fillColor = ((x / GRID_SIZE) + (y / GRID_SIZE)) % 2 == 0 ? FIELD_COLOR : ALT_FIELD_COLOR;
                SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
                SDL_RenderFillRect(renderer, &fieldRect);

                // Render text
                SDL_Color textColor = { 255, 255, 255, 255 }; // White color for the text
                if (y == WINDOW_HEIGHT-GRID_SIZE) {
                    std::string text = std::to_string(foo); // Convert integer to string
                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor); // "1" is the index, replace as needed
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    int indexX = x + GRID_SIZE - 20; // Adjust as needed for positioning
                    int indexY = y + GRID_SIZE - 20;
                    SDL_Rect textRect = { indexX, indexY, textSurface->w, textSurface->h };
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                    SDL_FreeSurface(textSurface);
                    SDL_DestroyTexture(textTexture);
                }
            }
            foo++;
        }

        // Update the window
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}