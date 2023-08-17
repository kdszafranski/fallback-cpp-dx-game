// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "ship.h"

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
    currentSpeed = shipNS::SPEED;
    hasPowerUp = false;

    spriteData.width = shipNS::WIDTH;           // size of ship
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   // location on screen
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = shipNS::WIDTH;

    // set bounding box for BOX colliders
    collisionType = entityNS::BOX;
    edge.top = -shipNS::HEIGHT / 2;    // -16
    edge.right = shipNS::WIDTH / 2;    // 64
    edge.bottom = shipNS::HEIGHT / 2;  // 16
    edge.left = -shipNS::WIDTH / 2;    // -64

    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = shipNS::SHIP_ANIMATION_DELAY;
    startFrame = shipNS::SHIP_START_FRAME;     // first frame of ship animation
    endFrame     = shipNS::SHIP_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0;
    mass = shipNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw()
{
    if (hasPowerUp) {
        Image::draw(graphicsNS::FB_METAL);
    } else {
        Image::draw(); // white
    }
}

//=============================================================================
// apply the given power up
//=============================================================================
void Ship::applyPowerUp(POWERUP type)
{
    // apply relevant power up
    if (type == FAST) {
        // bump our speed
        currentSpeed *= 1.5;
    }
    if (type == GROW) {
        // adjust spriteData and collider 
        // box collider now uses xScale for bounds
        grow();
    }
    
    hasPowerUp = true;
}

void Ship::grow()
{
    spriteData.xScale *= 1.5f;  // for drawing
    spriteData.width = 192;     // needed for drawing, fucks with collisions
    // collisions sizing
    edge.right = spriteData.width / 2;    // 96
    edge.left = -spriteData.width / 2;    // -96
}

void Ship::resetSize()
{
    spriteData.xScale = 1;
    spriteData.width = shipNS::WIDTH;
    edge.right = spriteData.width / 2;    // 64
    edge.left = -spriteData.width / 2;
}

//=============================================================================
// remove power ups
//=============================================================================
void Ship::removePowerUp()
{
    currentSpeed = shipNS::SPEED;
    resetSize();

    hasPowerUp = false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
    // move right
    if (input->isKeyDown(SHIP_RIGHT_KEY)) {
        spriteData.x += frameTime * currentSpeed;
    }

    // move left
    if (input->isKeyDown(SHIP_LEFT_KEY)) {
       spriteData.x -= frameTime * currentSpeed;
    }

    // keep it on the screen
    if (spriteData.x > GAME_WIDTH - spriteData.width) {
        spriteData.x = GAME_WIDTH - spriteData.width;    // position at right screen edge
    } else if (spriteData.x < 0) {
        spriteData.x = 0;                             // position at left screen edge
    }

}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{

}

