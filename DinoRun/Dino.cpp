//
//  Dino.cpp
//  DinoRun
//
//  Created by Marshall Brock on 2/28/24.
//

#include "Dino.hpp"

void Dino::Update()
{
    dinoY += static_cast<int>(dinoYVelocity);
    dinoYVelocity+=GRAVITY;
    //remember screen coordinates start at top left where it is 0,0 so the lower in the screen the greater the y value
    if(dinoY>=Utils::HEIGHT-48-40)
    {
        dinoY = Utils::HEIGHT-48-40;
        dinoYVelocity = 0.0;
        isJumping=false;
    }
}
void Dino::HandleJump()
{
    if(!isJumping)
    {
        dinoYVelocity = -JUMP_FORCE;
        isJumping = true;
    }
}





