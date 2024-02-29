//
//  Ground.cpp
//  DinoRun
//
//  Created by Marshall Brock on 2/29/24.
//

#include "Ground.hpp"

void Ground::Update()
{
    //update ground position for continuous scrolling
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

void Ground::SetWidth(const int& width) 
{    
    groundImageWidth = width;
}
