#include "Button.h"

Button::Button() : Image()
{
	defaultColor = graphicsNS::ALPHA75;
	mouseOverColor = graphicsNS::WHITE;

	colorFilter = defaultColor;
}

bool Button::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    input = gamePtr->getInput();

    return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Button::update(float frameTime)
{
    const float mouseX = input->getMouseX();
    const float mouseY = input->getMouseY();
    const float myX = getX();
    const float myY = getY();

    if (
        (mouseX >= myX && mouseX < myX + getWidth()) &&
        (mouseY >= myY && mouseY < myY + getHeight())
    )
    {
        // on mouseover
        colorFilter = mouseOverColor;
    } else {
        // mouse not over us
        colorFilter = defaultColor;
    }
}

void Button::draw()
{
    Image::draw(colorFilter);
}