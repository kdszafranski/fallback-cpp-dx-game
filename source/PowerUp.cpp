#include "PowerUp.h"

PowerUp::PowerUp(POWERUP pType, VECTOR2 position) : Entity()
{
    type = pType;
    spriteData.width = powerupNS::WIDTH;           // size of powerup
    spriteData.height = powerupNS::WIDTH;
    spriteData.x = position.x;                   // location on screen
    spriteData.y = position.y;
    spriteData.scale = 1;
    visible = true;

    collisionType = entityNS::BOX;                  // override's Image default to CIRCLE

    // set bounding box for BOX collider
    edge.top = -powerupNS::HEIGHT / 2;    // -16
    edge.right = powerupNS::WIDTH / 2;    // 16
    edge.bottom = powerupNS::HEIGHT / 2;  // 16
    edge.left = -powerupNS::WIDTH / 2;    // -6

    velocity.x = 0;   // velocity X
    velocity.y = 0;   // velocity Y
    frameDelay = 1;

    setFrameByType();
}

bool PowerUp::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* powerupTexture)
{
    if (!diamond.initialize(gamePtr->getGraphics(), powerupNS::WIDTH, powerupNS::WIDTH, powerupNS::TEXTURE_COLS, powerupTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power up diamond image"));
        return false;
    }
    diamond.setPosition(getX(), getY()); // top left, will roatate around center
    diamond.setCurrentFrame(7);

    return(Entity::initialize(gamePtr, width, height, ncols, powerupTexture));
}

void PowerUp::draw()
{
    diamond.draw(color); // orange
    Image::draw();
}

void PowerUp::update(float frameTime)
{
    Entity::update(frameTime);

    // just moves down
    spriteData.y += frameTime * powerupNS::SPEED;
    diamond.setY(diamond.getY() + frameTime * powerupNS::SPEED);

    // spin bg diamond
    diamond.setDegrees(diamond.getDegrees() + frameTime * 180);
}

void PowerUp::setFrameByType()
{
    setCurrentFrame(type);

    switch (type) {
    case SLOW:
    case FAST:
    case GROW:
        color = graphicsNS::FB_STRONG;
        break;
    case ZOOM:
    case TINY:
        color = graphicsNS::FB_HARD;        
        break;
    case WARP:
        color = graphicsNS::FB_METAL;
        break;
    case MYSTERY:
        color = graphicsNS::FB_INVINCIBLE;
    }
}