//
//  Ball.cpp
//  DeadLine
//
//  Created by six on 7/3/18.
//

#include "Ball.h"

Ball* Ball::create(int x, int y) {
    auto p = (Ball *) Sprite::create("glowing_ball.png");
    p->setScale(0.5);
    p->setPosition(Vec2(x, y));

    auto contentSize = p->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(contentSize.width , contentSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    
    physicsBody->setGravityEnable(true);
    physicsBody->setDynamic(true);
    p->setPhysicsBody(physicsBody);
    
    return p;
}
