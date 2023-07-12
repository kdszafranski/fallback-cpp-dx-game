// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provided by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "block.h"

//=============================================================================
// default constructor
//=============================================================================
Block::Block(BLOCK type) : Entity()
{
    // set values based on given type
    blockType = type;
    health = type + 1;
    pointValue = health * 5;

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

    isAnimating = false;
    originalScale = 1.0f;
    animScale = 1.0f;

    // set color based on type of block
    setBlockColorByType();

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
    // tint this block with its color filter
    Image::draw(color);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Block::update(float frameTime)
{
    if (isAnimating) {
        // scale
        float const scale = getScale();
        if (scale > animScale && scale < originalScale) {
            // go down
             setScale(getScale() - 0.025f);
        } else {
            if (scale > originalScale) {
                // done
                setScale(originalScale);
                isAnimating = false;
            } else {
                // going up
                animScale = originalScale; // need to keep going up
                setScale(getScale() + 0.025f);
            }
        }
    } else {
        // blocks don't move
        Entity::update(frameTime);
    }
}

//=============================================================================
// damage
//=============================================================================
void Block::damage(WEAPON weapon)
{
    if (weapon == BALL) {
        health = health - 1;
        if (health > 0) {
            // shift my type down
            blockType = static_cast<BLOCK>(blockType - 1);
            setBlockColorByType(); // update my color

            // animate the block
            bounceScale(1.0f, 0.75f);
        }
    }
}

void Block::setBlockColorByType()
{
    switch (blockType) {
        case WEAK:
            color = graphicsNS::FB_WEAK;
            break;
        case STRONG:
            color = graphicsNS::FB_STRONG;
            break;
        case HARD:
            color = graphicsNS::FB_HARD;
            break;
        case METAL:
            color = graphicsNS::FB_METAL;
            break;
        case INVINCIBLE:
            color = graphicsNS::FB_INVINCIBLE;
            break;
        }
}

void Block::bounceScale(float initialScale, float endScale)
{
    isAnimating = true;
    animScale = endScale;
    // needs to be less than originalScale
    setScale(0.999f);
}

