//
//  Ground.hpp
//  DinoRun
//
//  Created by Marshall Brock on 2/29/24.
//

#ifndef Ground_hpp
#define Ground_hpp

#include <stdio.h>
class Ground
{
private:
    int groundImageWidth = 0;
    int groundSpeed = 2;
    int ground1X = 0;
    int ground2X = 0;
public:
    void Update();
    int GetX1() const {return ground1X;}
    int GetX2() const {return ground2X;}
    void SetWidth(const int &width);
    int GetWidth() const {return groundImageWidth;};


};
#endif /* Ground_hpp */
