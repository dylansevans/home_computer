#include <SDL2/SDL.h>
#include "rendererclass.cpp"
#include <iostream>

int main()
{
    int width = 1920 / 4;
    int height = 1080 / 4;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Renderer myRenderer(width, height);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    bool quit = false;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        myRenderer.shift('U');
                        myRenderer.render(renderer);
                        break;
                    case SDLK_DOWN:
                        myRenderer.shift('D');
                        myRenderer.render(renderer);
                        break;
                    case SDLK_LEFT:
                        myRenderer.shift('L');
                        myRenderer.render(renderer);
                        break;
                    case SDLK_RIGHT:
                        myRenderer.shift('R');
                        myRenderer.render(renderer);
                        break;
                    case SDLK_1:
                        myRenderer.change_quality((int) Quality::LOW);
                        std::cout << "QUALITY LOW" << std::endl;
                        break;
                    case SDLK_2:
                        myRenderer.change_quality((int) Quality::MEDIUM);
                        std::cout << "QUALITY MEDIUM" << std::endl;
                        break;
                    case SDLK_3:
                        myRenderer.change_quality((int) Quality::HIGH);
                        std::cout << "QUALITY HIGH" << std::endl;
                        break;
                    case SDLK_4:
                        myRenderer.change_quality((int) Quality::ULTRA);
                        std::cout << "QUALITY ULTRA" << std::endl;
                        break;
                    case SDLK_5:
                        myRenderer.render(renderer);
                        break;
                    default:
                        std::cout << "Some other key pressed." << std::endl;
                        break;
                }
            } else if (e.type == SDL_MOUSEWHEEL) {
                if (e.wheel.y > 0) {
                    myRenderer.change_zoom(1);
                    myRenderer.render(renderer);
                } else {
                    myRenderer.change_zoom(0);
                    myRenderer.render(renderer);
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}