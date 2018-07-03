//
//  Brick.h
//  DeadLine
//
//  Created by six on 7/3/18.
//

#ifndef Brick_h
#define Brick_h

#include "cocos2d.h"
using namespace cocos2d;

class Brick : public Sprite {
private:
    int x, y;
    
public:
    static Brick* create(int x, int y);
};

#endif /* Brick_h */
