#include "textButton.h"

TextButton::TextButton()
{
    text = "Button";
    defaultColor = graphicsNS::TEAL;
    mouseOverColor = graphicsNS::WHITE;
}

TextButton::~TextButton()
{
    dxFont.onResetDevice();
}

bool TextButton::initialize(Game* game, int width, int height, int ncols,
    TextureManager* textureM)
{
    if (!dxFont.initialize(game->getGraphics(), 24, true, false, "Arial"))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button text font"));
        return false;
    }

    dxFont.setFontColor(defaultColor);

    return(Button::initialize(game, width, height, ncols, textureM));
}

/// <summary>
/// Adjust our own drawing RECT to be within our containing Button 
/// Must be called AFTER initialization
/// </summary>
void TextButton::calculateDrawRect()
{
    // using world coords... relative would be better, but... alas
    drawRect.left = getX(); // upper left X
    drawRect.top = getY();  // upper left Y
    drawRect.right = drawRect.left + getWidth();  // lower right X
    drawRect.bottom = drawRect.top + getHeight(); // lower right Y
}

void TextButton::update(float frameTime)
{
    // nothing to do right now
}

void TextButton::draw()
{
    //Image::draw(colorFilter);    
    dxFont.print(text, drawRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool TextButton::isMouseOver()
{
    if (Button::isMouseOver()) {
        // do our own thing
        dxFont.setFontColor(mouseOverColor);
        return true;
    } else {
        dxFont.setFontColor(defaultColor);
        return false;
    }

    return false;
}