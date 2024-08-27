#include <stdio.h>
#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* screen = SDL_CreateWindow("My SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    // Your rendering code goes here

    SDL_Delay(2000); // Wait for 2 seconds
    SDL_FillRect(*renderer, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    SDL_UpdateWindowSurface(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}

void drawPixel(SDL_Surface *Surface, int x, int y) {
    Uint8 *pixel_array = (Uint8 *)Surface->pixels;
    Uint8 *pixel = pixel_array + Surface->pitch * y + x;
    *pixel = SDL_MapRGB(Surface->format, 0, 0, 0); // Set pixel color (black)
}
