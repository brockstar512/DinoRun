#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
const int WIDTH = 640, HEIGHT = 360;

int main(int argc, char* argv[]) {
    
//    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    // Create a window
//    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//    if (window == NULL) {
//        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    // Create a renderer
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == NULL) {
//        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    //initialize image
//    if(!(IMG_Init(IMG_INIT_PNG)&& IMG_INIT_PNG))
//    {
//        std::cout<<"Could not initialize sdl_image:"<<IMG_GetError()<<std::endl;
//        return 1;
//    }

    
//check sdl
//    // Main loop
//    bool quit = false;
//    SDL_Event e;
//    while (!quit) {
//        while (SDL_PollEvent(&e) != 0) {
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // Clear the screen
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        // Update your rendering here
//
//        // Present the renderer
//        SDL_RenderPresent(renderer);
//    }
//
//    // Cleanup and quit
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
    
    SDL_Surface *imageSurface = NULL;
       SDL_Surface *windowSurface = NULL;
       
       SDL_Init( SDL_INIT_EVERYTHING );
       
       SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
       windowSurface = SDL_GetWindowSurface( window );
       
       // Check that the window was successfully created
       if ( NULL == window )
       {
           // In the case that the window could not be made...
           std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
           return 1;
       }
       
       if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
       {
           std::cout << "Could not create window: " << IMG_GetError( ) << std::endl;
           return 1;
       }
       
       SDL_Event windowEvent;
       
       imageSurface = IMG_Load("/Users/marshallbrock/Documents/C++/DinoRun/DinoRun/logo.png");
       
       if ( NULL == imageSurface )
       {
           std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;
       }
       
       while ( true )
       {
           if ( SDL_PollEvent( &windowEvent ) )
           {
               if ( SDL_QUIT == windowEvent.type )
               {
                   break;
               }
           }
           
           SDL_BlitSurface( imageSurface, NULL, windowSurface, NULL );
           
           SDL_UpdateWindowSurface( window );
       }
       
       SDL_FreeSurface( imageSurface );
       SDL_FreeSurface( windowSurface );
       
       imageSurface = NULL;
       windowSurface = NULL;
       
       SDL_DestroyWindow( window );
       SDL_Quit( );
       
       return EXIT_SUCCESS;
}
