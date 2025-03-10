#define SDL_MAIN_HANDLED

#include <stdio.h>
#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

int main(int argc, char* args[]){
    
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL couldn't initialize!, SDL_Error:%s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL Zeldalike",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    if (window == NULL){
        printf("Window couldn't be created! SDL_ERROR:%s\n", SDL_GetError());
        return -1;
    }

    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xff, 0xff, 0xff));
    SDL_UpdateWindowSurface(window);
    
    SDL_Event event;
    bool quit = false;
    while(!quit){

        while(SDL_PollEvent(&event)){

            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }

        }
    }

    return 1;
}