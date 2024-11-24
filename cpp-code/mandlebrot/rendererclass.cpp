#include <complex.h>
#include <SDL2/SDL.h>
#include <iostream>

enum class Quality : int {
    LOW = 4,
    MEDIUM = 20,
    HIGH = 50,
    ULTRA = 1000,
};

class Renderer 
{
    private:
        int width;
        int height;
        float centerx;
        float centery;
        int quality;
        float scale = 1;
        // SDL_Renderer* rend = nullptr;

    public:
        void render(SDL_Renderer* renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            float x;
            float y = centery - 1 * scale;
            const float startx = centerx - 1 * scale;
            float incrementx = (2 * scale) / width;
            float incrementy = (2 * scale) / height;
            for (int i = 0; i < height; i++) {
                x = startx;
                for (int j = 0; j < width; j++) {
                    if (get_color(x, y)) {
                        SDL_RenderDrawPoint(renderer, j, i);
                    }
                    x += incrementx;
                }
                y += incrementy;
            }
            SDL_RenderPresent(renderer);
        }

        int get_color(float a, float b) {
            std::complex<float> myComp(a, b);
            std::complex<float> init(a, b);
            float init_size = abs(init);

            for (int x = 0; x < quality; x++) {
                myComp = myComp * myComp + init;
                if (abs(myComp) > init_size * 2) {
                    return 0;
                }
            }
            float size = std::abs(myComp);
            if (size < 2) {
                return 1;
            }
            return 0;
        }

        void change_quality(int new_quality) {
            quality = new_quality;
        }

        void change_zoom(int isup) {
            if (isup) {
                scale *= .8;
            } else {
                scale *= 1.2;
            }
        }

        void shift(char type) {
            switch (type) {
                case 'L':
                    centerx -= .2 * scale;
                    break;
                case 'R':
                    centerx += .2 * scale;
                    break;
                case 'U':
                    centery -= .2 * scale;
                    break;
                case 'D':
                    centery += .2 * scale;
                    break;
                default:
                    std::cout << "COMMAND NOT FOUND" << std::endl;
            }
        }

        Renderer(int input_width, int input_height) {
            width = input_width;
            height = input_height;
            centerx = 0;
            centery = 0;
            quality = (int) Quality:: MEDIUM;
            // rend = renderer;
        }
};