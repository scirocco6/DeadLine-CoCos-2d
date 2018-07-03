//
//  Player.cpp
//  DeadLine
//
//  Created by six on 7/2/18.
//

#include "Player.h"

Player* Player::create() {
    auto p = (Player *) Sprite::create("wooden_paddle.png");
    
    auto contentSize = p->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(contentSize.width , contentSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));

    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(false);
    p->setPhysicsBody(physicsBody);
    
    return p;
}
