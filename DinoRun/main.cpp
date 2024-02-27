#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>


const int WIDTH = 640, HEIGHT = 360;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const char* SPRITES_FOLDER="/Users/marshallbrock/Documents/C++/DinoRun/DinoRun/sprites/";

//dino variables
int dinoX = 100;
int dinoY = HEIGHT - 48 - 40;
double dinoXVelocity = 0.0;
double dinoYVelocity = 0.0;
SDL_Texture* dinoTexture = NULL;
SDL_Texture* groundTexture1=NULL;
SDL_Texture* groundTexture2=NULL;
int groundImageWidth = 0;
int groundSpeed = 2;
int ground1X = 0;
int ground2X = 0;

const double GRAVITY = 0.1;
const double JUMP_FORCE = 6.0;
bool isJumping = false;

bool LoadSprites()
{
    std::string dinoPathImage = SPRITES_FOLDER + std::string("dino_.png");
    SDL_Surface *dinoSurface = IMG_Load(dinoPathImage.c_str());
    if(!dinoSurface)
    {
        std::cout<<"Problem loading Dino Image" << IMG_GetError()<<std::endl;
        return false;
    }
    dinoTexture = SDL_CreateTextureFromSurface(renderer,dinoSurface);
    SDL_FreeSurface(dinoSurface);
    return true;
}

bool InitializeSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Dino Run", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    
    
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

bool quit = false;
SDL_Event event;

void HandleJump()
{
    if(!isJumping)
    {
        dinoYVelocity = -JUMP_FORCE;
        isJumping = true;
    }
}
void UpdateDino()
{
    dinoY += static_cast<int>(dinoYVelocity);
    dinoYVelocity+=GRAVITY;
    //remember screen coordinates start at top left where it is 0,0 so the lower in the screen the greater the y value
    if(dinoY>=HEIGHT-48-40)
    {
        dinoY = HEIGHT-48-40;
        dinoYVelocity = 0.0;
        isJumping=false;
    }
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
                 HandleJump();
             }
            }
        }
        UpdateDino();
        
        //color background
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        //clear frame to update ever loop
        SDL_RenderClear(renderer);
        //where i want image to show on x and y image
        SDL_Rect dinoRect = {dinoX,dinoY,44,48};
        //copy image to paste on window...this just renders one item
        SDL_RenderCopy(renderer,dinoTexture,NULL,&dinoRect);
        
        //present everything that the renderer has
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1);
    }

    SDL_Quit();
}
