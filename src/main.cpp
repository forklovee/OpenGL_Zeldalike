#define SDL_MAIN_HANDLED

#include <stdio.h>
#include "SDL2/SDL.h"

#include "glad/glad.h"

int main(int argc, char* args[]){
    
    SDL_Window *window;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL error %s\n", SDL_GetError());
        return -1;
    }
    SDL_GLContext context;

    // Specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Request a window
    window = SDL_CreateWindow(
        "Zeldalike SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );

    // Check if window was created successfully.
    if (!window){
        printf("Window couldn't get created! error: %s", SDL_GetError());
        return -1;
    }

    // Create OpenGL context.
    context = SDL_GL_CreateContext(window);
    
    // Check if context got created.
    if (!context){
        printf("OpenGL context couldn't get created! error: %s", SDL_GetError());
        return -1;
    }

    // Setup function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    // "infinite" loop.
    bool isGameRunning = true;
    while (isGameRunning)
    {
        glViewport(0, 0, 1280, 720);

        // event loop
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type){
                case SDL_MOUSEMOTION:
                    printf("mouse moving!\n");
                    break;
                case SDL_QUIT:
                    isGameRunning = false;
                    break;
            }

            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT])
            {
                printf("right arrow pressed!\n");
            }
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        SDL_GL_SwapWindow(window);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}