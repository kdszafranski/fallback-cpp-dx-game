#include "blockButton.h"

BlockButton::BlockButton(BLOCK type)
{
    blockType = type;
}

BlockButton::~BlockButton()
{

}

void BlockButton::draw()
{
    Image::draw(graphicsNS::WHITE);
}

void BlockButton::setBlockColorByType()
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