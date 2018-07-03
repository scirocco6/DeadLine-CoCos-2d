//
//  Brick.cpp
//  DeadLine
//
//  Created by six on 7/3/18.
//

#include "Brick.h"

Brick* Brick::create(int x, int y) {
    auto p = (Brick *) Sprite::create("rainbow_brick_glow.png");
    
    p->setPosition(Vec2(x, y));
    
    auto contentSize = p->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(contentSize.width , contentSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    
    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(false);
    p->setPhysicsBody(physicsBody);
    
    
    return p;
}
