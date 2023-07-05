// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "ball.h"

//=============================================================================
// default constructor
//=============================================================================
Ball::Ball() : Entity()
{
    spriteData.width = ballNS::WIDTH;           // size of Ball
    spriteData.height = ballNS::HEIGHT;
    spriteData.x = ballNS::X;                   // location on screen
    spriteData.y = ballNS::Y;

    // set bounding box for BOX collider
    collisionType = entityNS::BOX;      // override's Image default to CIRCLE
    edge.top = -ballNS::HEIGHT / 2;     // -8
    edge.right = ballNS::WIDTH / 2;     // 8
    edge.bottom = ballNS::HEIGHT / 2;   // 8
    edge.left = -ballNS::WIDTH / 2;     // -8

    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = 1;

    startFrame = ballNS::BALL_START_FRAME;     // first frame of ship animation
    endFrame = ballNS::BALL_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    
    radius = ballNS::WIDTH / 2.0;
    mass = ballNS::MASS;

    collisionType = entityNS::BOX;
}


//=============================================================================
// Initialize the Ball.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ball::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ball
//=============================================================================
void Ball::draw()
{
    Image::draw();              // draw ball
}

//=============================================================================
// Ball bounces off a BOX collider entity
//=============================================================================
void Ball::bounce(VECTOR2& collisionVector, SpriteData otherSpriteData)
{
    const float myX = getX();
    const float myY = getY();
    // total right-edge x position of other entity
    const float boxWidth = (otherSpriteData.x + otherSpriteData.width);
    // total bottom y position of other entity
    const float boxHeight = (otherSpriteData.y + otherSpriteData.height);

    // above or below
    if (
        (myX > otherSpriteData.x && myY < otherSpriteData.y) || // above
        (myX > otherSpriteData.x && myY + spriteData.y > boxHeight) // below
        )
    {
        velocity.y = -velocity.y;
    }

    // left or right
    if (
        (myX < otherSpriteData.x && myY > otherSpriteData.y) ||     // left
        (myX > boxWidth && myY > otherSpriteData.y)  // right
        )
    {
        velocity.x = -velocity.x;
    }

    audio->playCue(CLUNK); 
}

/// <summary>
/// Allows basic left, normal, right aiming based on where the ball hits
/// Still uses constant 250 y velocity
/// </summary>
/// <param name="collisionVector"></param>
/// <param name="collisionPosition"></param>
/// <param name="otherSpriteData"></param>
void Ball::bounceOffShip(VECTOR2& collisionVector, VECTOR2& collisionPosition, SpriteData otherSpriteData)
{
    // determine WHERE along the ship we hit
    const float myX = getX();
    const float myY = getY();
    const float middleX = otherSpriteData.width / 3; // middle third of ship
    const float rightX = middleX * 2; // right-hand third of ship

    // get ship-relative position
    collisionPosition.x = myX - otherSpriteData.x;
    collisionPosition.y = myY - otherSpriteData.y;

    if (collisionPosition.x < middleX) {
        // left-hand side, aim left
        velocity.y = -velocity.y;
        velocity.x = -250;
        //velocity.x = 
    } else if(collisionPosition.x > middleX && collisionPosition.x < rightX) {
        // middle, just reflect
        velocity.y = -velocity.y;
    } else {
        // right third, aim right
        velocity.y = -velocity.y;
        velocity.x = 250;
    }

    // total right-edge x position of other entity
    const float boxWidth = (otherSpriteData.x + otherSpriteData.width);
    // total bottom y position of other entity
    const float boxHeight = (otherSpriteData.y + otherSpriteData.height);

    // above or below
    //if (
    //    (myX > otherSpriteData.x && myY < otherSpriteData.y) || // above
    //    (myX > otherSpriteData.x && myY + spriteData.y > boxHeight) // below
    //    )
    //{
    //    velocity.y = -velocity.y;
    //}

    // left or right
    //if (
    //    (myX < otherSpriteData.x && myY > otherSpriteData.y) ||     // left
    //    (myX > boxWidth && myY > otherSpriteData.y)  // right
    //    )
    //{
    //    velocity.x = -velocity.x;
    //}

    audio->playCue(CLUNK);

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ball::update(float frameTime)
{
    Entity::update(frameTime);
    
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y

    // Bounce off walls
    // NOT done with actual collisions, this is done strictly from screen position
    if (spriteData.x > GAME_WIDTH - ballNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH - ballNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
        audio->playCue(CLICK);
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
        audio->playCue(CLICK);
    }
    
    if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
        audio->playCue(CLICK);
    }
}

//=============================================================================
// damage
//=============================================================================
void Ball::damage(WEAPON weapon)
{

}

