#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "Utils.hpp"
#include "Dino.hpp"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* dinoTexture = NULL;
SDL_Texture* groundTexture1=NULL;
SDL_Texture* groundTexture2=NULL;
int groundImageWidth = 0;
int groundSpeed = 2;
int ground1X = 0;
int ground2X = 0;

bool quit = false;
SDL_Event event;

Dino* dino;

bool LoadSprites()
{
    std::string dinoPathImage = Utils::SPRITES_FOLDER + std::string("dino_.png");
    std::string groundPathImage = Utils::SPRITES_FOLDER + std::string("ground.png");
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
    
    groundImageWidth=groundSurface->w;
    SDL_FreeSurface(groundSurface);
    return true;
}
//update ground position for continuous scrolling
void UpdateGround()
{
    ground1X -= groundSpeed;
    ground2X -= groundSpeed;
    //if ground 1 is all the way hidden at that point and we know this by adding the width to it and it is still less than 0
    if(ground1X + groundImageWidth < 0)
    {
        ground1X = ground2X + groundImageWidth;
    }
    else if(ground2X + groundImageWidth){
        ground2X = ground1X + groundImageWidth;
    }
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
    UpdateGround();
    //color background
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    //clear frame to update ever loop
    SDL_RenderClear(renderer);
    //where i want image to show on x and y image
    SDL_Rect dinoRect = dino->GetRect();
    SDL_Rect groundRect1 = {ground1X,Utils::HEIGHT-40-48, groundImageWidth,40};
    SDL_RenderCopy(renderer,groundTexture1,NULL,&groundRect1);
    SDL_Rect groundRect2 = {ground2X,Utils::HEIGHT-40-48, groundImageWidth,40};
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
    //game loop
    while(!quit)
    {
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
        
        SDL_Delay(1);
    }

    SDL_Quit();
}



