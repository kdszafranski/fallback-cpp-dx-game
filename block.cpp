// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "block.h"

//=============================================================================
// default constructor
//=============================================================================
Block::Block() : Entity()
{
    spriteData.width = blockNS::WIDTH;           // size of Ball
    spriteData.height = blockNS::HEIGHT;
    spriteData.x = blockNS::X;                   // location on screen
    spriteData.y = blockNS::Y;

    // set bounding box for BOX collider
    collisionType = entityNS::BOX;      // override's Image default to CIRCLE
    edge.top = -blockNS::HEIGHT / 2;     // -32
    edge.right = blockNS::WIDTH / 2;     // 32
    edge.bottom = blockNS::HEIGHT / 2;   // 32
    edge.left = -blockNS::WIDTH / 2;     // -32

    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = 1;

    startFrame = blockNS::BLOCK_START_FRAME;     // first frame of ship animation
    endFrame = blockNS::BLOCK_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;

    radius = blockNS::WIDTH / 2.0;
    mass = blockNS::MASS;
    collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Block.
// Post: returns true if successful, false if failed
//=============================================================================
bool Block::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the block
//=============================================================================
void Block::draw()
{
    Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Block::update(float frameTime)
{
    // blocks don't move
    Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Block::damage(WEAPON weapon)
{
}

