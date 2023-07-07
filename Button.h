#pragma once

#include "image.h"
#include "game.h"
#include "input.h"

/// <summary>
/// UI Buttons, extends Image
/// </summary>
class Button : public Image
{
private:

	TextureManager buttonTexture;
	COLOR_ARGB defaultColor;
	COLOR_ARGB mouseOverColor;
	Input *input;


public:

	Button();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw();
};

