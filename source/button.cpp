#include "Button.h"

Button::Button() : Image()
{
	defaultColor = buttonNS::DEFAULT_COLOR;
	mouseOverColor = buttonNS::MOUSE_OVER_COLOR;

	colorFilter = defaultColor;
}

Button::~Button()
{

}

bool Button::initialize(Game* game, int width, int height, int ncols, TextureManager* textureM)
{
    input = game->getInput();

    return(Image::initialize(game->getGraphics(), width, height, ncols, textureM));
}

void Button::update(float frameTime)
{
    // nothing to do right now
}

void Button::draw(COLOR_ARGB otherColor) {
    Image::draw(otherColor);
}

void Button::draw(bool fromCenter)
{
    Image::draw(colorFilter, fromCenter);
}


bool Button::isMouseOver()
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
        return true;
    }
    
    // mouse not over us
    colorFilter = defaultColor;
    return false;
}