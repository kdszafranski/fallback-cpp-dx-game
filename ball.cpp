// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

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
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ball::update(float frameTime)
{
    Entity::update(frameTime);
    //spriteData.angle += frameTime * ballNS::ROTATION_RATE;  // rotate the ship
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y

    // Bounce off walls
    if (spriteData.x > GAME_WIDTH - ballNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH - ballNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT - ballNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT - ballNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
}

//=============================================================================
// damage
//=============================================================================
void Ball::damage(WEAPON weapon)
{

}

