#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
const int GRID_SIZE = 80; // Adjust the grid size as needed
const SDL_Color GRID_COLOR = { 100, 100, 100, 255 }; // Adjust the grid color a
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
                                          SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
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
        } // Rendering code
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color to white
        SDL_RenderClear(renderer); // Clear the renderer with white color

        // Draw grid
        SDL_SetRenderDrawColor(renderer, GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b, GRID_COLOR.a);
        for (int x = 0; x < WINDOW_HEIGHT; x += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT); // Vertical lines
        }
        for (int y = 0; y < WINDOW_WIDTH; y += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y); // Horizontal lines
        }

        for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
            for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
                SDL_Rect fieldRect = { x, y, GRID_SIZE, GRID_SIZE };
                SDL_Color fillColor;
                 if (((x / GRID_SIZE) + (y / GRID_SIZE)) % 2 == 0) {
                     fillColor = FIELD_COLOR;
                 } else {
                     fillColor = ALT_FIELD_COLOR;
                 }
                SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
                SDL_RenderFillRect(renderer, &fieldRect);
                
            }
        }

        SDL_RenderPresent(renderer); // Update the window

        // Render code can be added here
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
