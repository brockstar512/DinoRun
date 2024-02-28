//
//  Dino.hpp
//  DinoRun
//
//  Created by Marshall Brock on 2/28/24.
//

#ifndef Dino_hpp
#define Dino_hpp

#include <stdio.h>
#include "Utils.hpp"
#include <SDL2/SDL.h>
class Dino{
    
public:
    void Update();
    void HandleJump();
    SDL_Rect GetRect() const {return {dinoX,dinoY,44,48};}
    
    
    
private:
    int dinoX = 100;
    int dinoY = Utils::HEIGHT - 48 - 40;
    double dinoXVelocity = 0.0;
    double dinoYVelocity = 0.0;
    const double GRAVITY = 0.1;
    const double JUMP_FORCE = 6.0;
    bool isJumping = false;
};
#endif /* Dino_hpp */
