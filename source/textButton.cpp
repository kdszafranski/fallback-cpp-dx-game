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
    if (dxFont.initialize(game->getGraphics(), 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button text font"));

    return(Button::initialize(game, width, height, ncols, textureM));
}

void TextButton::update(float frameTime)
{
    // nothing to do right now
}

void TextButton::draw()
{
    Image::draw(colorFilter);
    dxFont.setFontColor(graphicsNS::TEAL);
    dxFont.print(text, getCenterX(), getCenterX());
}