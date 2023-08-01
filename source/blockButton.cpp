#include "blockButton.h"

BlockButton::BlockButton(BLOCK type)
{
    blockType = type;
    // override colors
    mouseOverColor = graphicsNS::BROWN;
    setBlockColorByType();

}

BlockButton::~BlockButton()
{

}

void BlockButton::draw()
{
    Button::draw();
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
    case NONE:
        color = graphicsNS::FB_EDITOR_NONE;
        break;
    }

    defaultColor = color;
}

void BlockButton::changeBlockType()
{
    blockType = WEAK;
    setBlockColorByType();
}