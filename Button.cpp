#include "Button.h"

Button::Button()
{
	colorFilter = graphicsNS::WHITE;
}

Button::~Button()
{

}

bool Button::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    input = gamePtr->getInput();
    return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Button::update(float frameTime)
{

}

void Button::draw()
{
    Image::draw();
}