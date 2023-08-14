#include "PowerUp.h"

PowerUp::PowerUp(POW t) : Entity()
{
    type = t;
    spriteData.width = powerupNS::WIDTH;           // size of Ball
    spriteData.height = powerupNS::WIDTH;
    spriteData.x = powerupNS::X;                   // location on screen
    spriteData.y = powerupNS::Y;

    // set bounding box for BOX collider
    collisionType = entityNS::BOX;      // override's Image default to CIRCLE
    edge.top = -powerupNS::HEIGHT / 2;    // -16
    edge.right = powerupNS::WIDTH / 2;    // 16
    edge.bottom = powerupNS::HEIGHT / 2;  // 16
    edge.left = -powerupNS::WIDTH / 2;    // -6

    velocity.x = 0;   // velocity X
    velocity.y = 0;   // velocity Y
    frameDelay = 1;

    startFrame = 0;     // first frame of ship animation
    endFrame = 0;     // last frame of ship animation
    currentFrame = startFrame;
}

bool PowerUp::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void PowerUp::draw()
{
    Image::draw();
}

void PowerUp::update(float frameTime)
{
    Entity::update(frameTime);

    // just moves down
    spriteData.y += frameTime * velocity.y;
}