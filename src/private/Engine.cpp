// #include "Engine.h"



// namespace Engine{
//     Game::Game()
//     {
        
//     }

//     bool Game::init(){
//         if(SDL_Init(SDL_INIT_VIDEO) < 0){
//             printf("SDL couldn't initialize!, SDL_Error:%s\n", SDL_GetError());
//             return false
//         }

//         window = SDL_CreateWindow(game_name,
//             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//             window_width, window_height,
//             SDL_WINDOW_SHOWN);
        
//         if (window == NULL){
//             printf("Window couldn't be created! SDL_ERROR:%s\n", SDL_GetError());
//             return false;
//         }

//         screen_surface = SDL_GetWindowSurface(window);
//         SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xff, 0xff, 0xff));
//         SDL_UpdateWindowSurface(window);

//         return true;
//     }

//     bool Game::loadMedia(){
//         return true;
//     }

//     void Game::close(){
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//     }

// }