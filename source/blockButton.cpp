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

void BlockButton::changeBlockType(BLOCK type)
{
    blockType = type;
    setBlockColorByType();
}

void BlockButton::setBlockColorByType()
{
    switch (blockType) {
    case WEAK:
        defaultColor = graphicsNS::FB_WEAK;
        break;
    case STRONG:
        defaultColor = graphicsNS::FB_STRONG;
        break;
    case HARD:
        defaultColor = graphicsNS::FB_HARD;
        break;
    case METAL:
        defaultColor = graphicsNS::FB_METAL;
        break;
    case INVINCIBLE:
        defaultColor = graphicsNS::FB_INVINCIBLE;
        break;
    case NONE:
        defaultColor = graphicsNS::FB_EDITOR_NONE;
        break;
    }

    colorFilter = defaultColor;
}
