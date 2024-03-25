#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "Utils.hpp"
#include "Dino.hpp"
#include "Ground.hpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* dinoTexture = NULL;
SDL_Texture* groundTexture1=NULL;
SDL_Texture* groundTexture2=NULL;

//frame rate
const unsigned int fps = 60;
const unsigned int desiredDelta = 1000/fps;

bool quit = false;
SDL_Event event;

Dino* dino = nullptr;
Ground* ground = nullptr;
const char* SPRITES_FOLDER="/Users/marshallbrock/Documents/C++/DinoRun/DinoRun/sprites/";
bool LoadSprites()
{
    std::string dinoPathImage = SPRITES_FOLDER + std::string("dino_.png");
    std::string groundPathImage = SPRITES_FOLDER + std::string("ground.png");
    SDL_Surface *dinoSurface = IMG_Load(dinoPathImage.c_str());
    if(!dinoSurface)
    {
        std::cout<<"Problem loading Dino Image" << IMG_GetError()<<std::endl;
        return false;
    }
    dinoTexture = SDL_CreateTextureFromSurface(renderer,dinoSurface);
    SDL_FreeSurface(dinoSurface);
    
    SDL_Surface *groundSurface = IMG_Load(groundPathImage.c_str());
    if(!dinoSurface)
    {
        std::cout<<"Problem loading ground Image" << IMG_GetError()<<std::endl;
        return false;
    }
//    dinoTexture = SDL_CreateTextureFromSurface(renderer,groundSurface);
    groundTexture1 = SDL_CreateTextureFromSurface(renderer,groundSurface);
    groundTexture2 = SDL_CreateTextureFromSurface(renderer,groundSurface);
    
//    groundImageWidth=groundSurface->w;
    ground = new Ground;
    ground->SetWidth(groundSurface->w);
    SDL_FreeSurface(groundSurface);
    return true;
}


bool InitializeSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Dino Run", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Utils::WIDTH,Utils::HEIGHT,SDL_WINDOW_SHOWN);
    
    
    if(!window){
        std::cout<<"SDL_CREATE window error"<<SDL_GetError()<<std::endl;
        SDL_Quit();
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    
    if(!renderer){
        std::cout<<"SDL_CREATE renderer error"<<SDL_GetError()<<std::endl;
        SDL_Quit();
        return false;
    }
    //5 seconds
    //SDL_Delay(10000);
    return true;
}


//this only handles the renderer
void Draw()
{
    dino->Update();
    ground->Update();
    //color background
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    //clear frame to update ever loop
    SDL_RenderClear(renderer);
    //where i want image to show on x and y image
    SDL_Rect dinoRect = {dino->GetX(),dino->GetY(),44,48};
    SDL_Rect groundRect1 = {ground->GetX1(),Utils::HEIGHT-40-48, ground->GetWidth(),40};
    SDL_RenderCopy(renderer,groundTexture1,NULL,&groundRect1);
    SDL_Rect groundRect2 = {ground->GetX2(),Utils::HEIGHT-40-48, ground->GetWidth(),40};
    SDL_RenderCopy(renderer,groundTexture2,NULL,&groundRect2);


    
    //copy image to paste on window...this just renders one item
    SDL_RenderCopy(renderer,dinoTexture,NULL,&dinoRect);
    
    //present everything that the renderer has
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    
    if(!InitializeSDL())
    {
        return 1;
    }
    if(!LoadSprites())
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    dino = new Dino;
    //game loop
    while(!quit)
    {
        //number returned is time in milliseconds sents sdl init was called
        int startLoop = SDL_GetTicks();
        
        
        //event loop
        while(SDL_PollEvent(&event)!=0)
        {

         if(event.type == SDL_QUIT)
         {
             quit = true;
         }
            //determine if any key is pressed
            else if (event.type == SDL_KEYDOWN)
            {
                //jump jump key is presed
             if(event.key.keysym.sym ==SDLK_UP || event.key.keysym.sym== SDLK_SPACE)
             {
                 dino->HandleJump();
             }
            }
        }
        
        Draw();
        int delta = SDL_GetTicks() - startLoop;
        
        if(delta < desiredDelta)
        {
            SDL_Delay(desiredDelta - delta);
        }
        //SDL_Delay(1);
    }
    delete dino;
    SDL_Quit();
}



