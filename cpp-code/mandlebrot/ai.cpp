#include <SDL2/SDL.h>
#include <iostream>
#include <complex>

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_ITER = 1000;
const double ZOOM_STEP = 1.2;
const double MOVE_STEP = 0.1;

struct MandelbrotParams {
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

void drawMandelbrot(SDL_Renderer* renderer, const MandelbrotParams& params) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double c_re = params.xMin + (x / (double)WIDTH) * (params.xMax - params.xMin);
            double c_im = params.yMin + (y / (double)HEIGHT) * (params.yMax - params.yMin);
            std::complex<double> c(c_re, c_im);
            std::complex<double> z(0);
            int iter = 0;
            while (std::abs(z) <= 2.0 && iter < MAX_ITER) {
                z = z * z + c;
                ++iter;
            }
            Uint8 color = static_cast<Uint8>(255 * iter / MAX_ITER);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    MandelbrotParams params = { -2.0, 1.0, -1.5, 1.5 };
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        params.yMin += MOVE_STEP * (params.yMax - params.yMin);
                        params.yMax += MOVE_STEP * (params.yMax - params.yMin);
                        break;
                    case SDLK_DOWN:
                        params.yMin -= MOVE_STEP * (params.yMax - params.yMin);
                        params.yMax -= MOVE_STEP * (params.yMax - params.yMin);
                        break;
                    case SDLK_LEFT:
                        params.xMin -= MOVE_STEP * (params.xMax - params.xMin);
                        params.xMax -= MOVE_STEP * (params.xMax - params.xMin);
                        break;
                    case SDLK_RIGHT:
                        params.xMin += MOVE_STEP * (params.xMax - params.xMin);
                        params.xMax += MOVE_STEP * (params.xMax - params.xMin);
                        break;
                    case SDLK_KP_PLUS:
                    case SDLK_EQUALS:
                        params.xMin += (params.xMax - params.xMin) * (1.0 - 1.0 / ZOOM_STEP);
                        params.xMax -= (params.xMax - params.xMin) * (1.0 - 1.0 / ZOOM_STEP);
                        params.yMin += (params.yMax - params.yMin) * (1.0 - 1.0 / ZOOM_STEP);
                        params.yMax -= (params.yMax - params.yMin) * (1.0 - 1.0 / ZOOM_STEP);
                        break;
                    case SDLK_KP_MINUS:
                    case SDLK_MINUS:
                        params.xMin -= (params.xMax - params.xMin) * (ZOOM_STEP - 1.0);
                        params.xMax += (params.xMax - params.xMin) * (ZOOM_STEP - 1.0);
                        params.yMin -= (params.yMax - params.yMin) * (ZOOM_STEP - 1.0);
                        params.yMax += (params.yMax - params.yMin) * (ZOOM_STEP - 1.0);
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMandelbrot(renderer, params);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}