#pragma once
#include "button.h"
#include "textDX.h"

class TextButton : public Button
{
private:
	std::string text;
	TextDX dxFont;

public:
	TextButton();
	~TextButton();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw();

	void setText(std::string newText) { text = newText; }
	std::string getText() { return text; }
};

