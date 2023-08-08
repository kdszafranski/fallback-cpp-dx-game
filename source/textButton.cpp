#include "textButton.h"

TextButton::TextButton()
{
    intValue = 0;
    text = "Button";
    fontSize = 32;
    defaultColor = graphicsNS::TEAL;
    mouseOverColor = graphicsNS::WHITE;
}

TextButton::~TextButton()
{
    //displayFont.onResetDevice();
}

bool TextButton::initialize(Game* game, int width, int height, int ncols,
    TextureManager* textureM)
{
    if (!displayFont.initialize(game->getGraphics(), fontSize, true, false, "Agdasima"))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button text font"));
        return false;
    }

    displayFont.setFontColor(defaultColor);

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
    displayFont.print(text, drawRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool TextButton::isMouseOver()
{
    if (Button::isMouseOver()) {
        // do our own thing
        displayFont.setFontColor(mouseOverColor);
        return true;
    } else {
        displayFont.setFontColor(defaultColor);
        return false;
    }

    return false;
}