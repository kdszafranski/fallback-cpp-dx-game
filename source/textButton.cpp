#include "textButton.h"

TextButton::TextButton()
{
    text = "Test";
}

TextButton::~TextButton()
{
    dxFont.onResetDevice();
}

bool TextButton::initialize(Game* game, int width, int height, int ncols,
    TextureManager* textureM)
{
    if (dxFont.initialize(game->getGraphics(), 24, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button text font"));

    dxFont.setFontColor(graphicsNS::TEAL);

    return(Button::initialize(game, width, height, ncols, textureM));
}

void TextButton::update(float frameTime)
{
    // nothing to do right now
}

void TextButton::draw()
{
    //Image::draw(colorFilter);
    // | is bitwise, each bit in the DWORD represents a formatting option
    // clever and efficient
    dxFont.print(text, spriteData.rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool TextButton::isMouseOver()
{
    if (Button::isMouseOver()) {
        // do our own thing
        dxFont.setFontColor(graphicsNS::WHITE);
        return true;
    } else {
        dxFont.setFontColor(graphicsNS::TEAL);
        return false;
    }

    return false;
}