#pragma once

#include "image.h"
#include "game.h"
#include "input.h"

namespace buttonNS {
	const COLOR_ARGB DEFAULT_COLOR = graphicsNS::ALPHA75;
	const COLOR_ARGB MOUSE_OVER_COLOR = graphicsNS::WHITE;
}

/// <summary>
/// UI Buttons, extends Image
/// </summary>
class Button : public Image
{
private:
	// colors
	COLOR_ARGB defaultColor;
	COLOR_ARGB mouseOverColor;

	TextureManager buttonTexture;
	Input *input;

public:

	Button();
	~Button();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw();

	// handlers
	bool isMouseOver();
};

