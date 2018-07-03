/****************************************************************************
 Copyright (c) 2018 dotSix LLC
****************************************************************************/

#include "DeadLineScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

// Sound and Music
#define BACKGROUND_MUSIC        "SpaceEmergency.mp3"

#define One_Up_Sound            "1Up.mp3"
#define Ball_Hits_Wall          "ball_hits_wall.mp3"
#define Ball_Hits_DeadLine      "ball_hits_DeadLine.mp3"
#define Ball_Hits_Falling_brick "ball_hits_falling_brick.mp3"
#define Ball_Hits_Paddle        "ball_hits_paddle.mp3"
#define Brick_Hits_Paddle       "brick_hits_paddle.mp3"
#define Brick_Hits_DeadLine2    "brick_hits_DeadLine2.mp3"
#define Brick_Learns_Gravity    "brick_learns_gravity.mp3"

enum class PhysicsCategory {
//    None = 0,
//    Monster = (1 << 0),    // 1
//    Projectile = (1 << 1), // 2
//    All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
    
    None              = 0,
    playfield         = (1 << 1),
    ball              = (1 << 2),
    player            = (1 << 3),
    brick             = (1 << 4),
    DeadLine          = (1 << 5),
    ballHitPlayfield  = playfield | ball,
    ballHitBrick      = ball      | brick,
    ballHitDeadLine   = DeadLine  | ball,
    brickHitDeadLine  = DeadLine  | brick,
    ballHitPaddle     = ball      | player,
    brickHitPaddle    = brick     | player
};

Scene* DeadLine::createScene() {
    auto scene = Scene::createWithPhysics();
    auto layer = DeadLine::create();
    scene->addChild(layer);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0, -92.0));
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DeadLineScene.cpp\n");
}

bool DeadLine::init() {
    if (!Layer::init()) {
        return false;
    }

    auto origin  = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();

    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.6,0.6,0.6,1.0));
    this->addChild(background);
    
    player = (Player *) Player::create();
    player->setPosition(Vec2(150, 100.0));
    this->addChild(player);

    SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC, true);
    
    newGame();
    return true;
}


void DeadLine::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void DeadLine::newGame() {
    for (auto brick = wall.begin(); brick != wall.end(); brick++) {
        brickDie(brick->first);
    }
    
    if (wall.size() == 0) wallUp();

    score    = 0;
    nextLife = 20000;
    balls    = 3;
    inPlay   = false;
    
    if (ball) ball->removeFromParentAndCleanup(true);
    
//    scoreBoard.text  = "0"
//
//    message.text     = "Ready Player One"
//    message.isHidden = false
//    lives.text       = "\(balls) Balls Left"
//    lives.isHidden   = false
    
    newBall();
}

void DeadLine::wallUp() {
    auto contentSize = this->getContentSize();
    int topY = contentSize.height;
    
    for (int y = topY - 50; y > topY - 190; y -= 40) {
        for (int x = 95; x < 965; x += 70) {
            
            printf("Adding brick at %i, %i\n", x, y);
            
            auto brick = Brick::create(x, y);
            brick->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::brick);
            this->addChild(brick);
            
            wall[brick] = true;
        }
    }
}

void DeadLine::brickDie(Brick *brick) {
    brick->removeFromParentAndCleanup(true);
    wall.erase(brick);
    
    if (wall.size() == 0) wallUp();
}

void DeadLine::newBall() {
    if (balls > 0) { // if no ball in play AND there are any left, launch one
        balls--;
        
//        message.isHidden = true
//        lives.isHidden   = true
        
        ball = Ball::create(200,200);
        this->addChild(ball);
        
//        ball?.physicsBody!.categoryBitMask    = ballCategory
//        ball?.physicsBody!.contactTestBitMask = playfieldCategory | deadlineCategory | playerCategory | brickCategory
//        ball?.run(scaleToNormal)
    }
    else {
        newGame();
    }
}
