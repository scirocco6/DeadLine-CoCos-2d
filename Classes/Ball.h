//
//  Ball.h
//  DeadLine
//
//  Created by six on 7/3/18.
//

#ifndef Ball_h
#define Ball_h

#include "cocos2d.h"
using namespace cocos2d;

class Ball : public Sprite {
public:
    static Ball* create(int x, int y);
};
#endif /* Ball_h */
