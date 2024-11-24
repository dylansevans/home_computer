#include <SDL2/SDL.h>
#include <complex.h>
#include <iostream>

void drawPixel(SDL_Surface* surface, int x, int y);
int getColorOfPixel(std::complex<double>& number, int accuracy);

void drawPixel(SDL_Surface* surface, int x, int y) {
    Uint8* pixel_array = (Uint8*)surface->pixels;
    Uint8* pixel = pixel_array + surface->pitch * y + x;
    for (int i = 0; i < surface->w; i++) {
        for (int j = 0; j < surface->h / 2; j++) {
            *(pixel_array + j * surface->pitch + i * surface->format->BytesPerPixel) = SDL_MapRGBA(surface->format, 0, 0, 0, 1);
        }
    }
}


int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Window* window = SDL_CreateWindow("Pixel Manipulation Example",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          960, 540, 0);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Get the window surface
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    // Fill the surface with a background color (white)
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    // Draw a black pixel at (100, 100)
    drawPixel(surface, 0, 0);

    // Update the window surface
    SDL_UpdateWindowSurface(window);

    // Event loop
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
