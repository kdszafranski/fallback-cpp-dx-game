#pragma once

#include "image.h"
#include "game.h"
#include "input.h"

namespace buttonNS {
	const COLOR_ARGB DEFAULT_COLOR = D3DCOLOR_ARGB(255, 247, 163, 114);
	const COLOR_ARGB MOUSE_OVER_COLOR = D3DCOLOR_ARGB(255, 166, 222, 226);
}

/// <summary>
/// UI Buttons, extends Image
/// </summary>
class Button : public Image
{
private:
	Input *input;

protected:
	// colors
	COLOR_ARGB defaultColor;
	COLOR_ARGB mouseOverColor;

public:

	Button();
	~Button();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw(COLOR_ARGB otherColor);
	virtual void draw(bool fromCenter = false);

	/// <summary>
	/// Determines if the mouse position is currently inside this rect
	/// </summary>
	/// <returns>
	/// true if inside
	/// false if not inside
	/// </returns>
	virtual bool isMouseOver();
};

