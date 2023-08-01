#pragma once
#include "button.h"
#include "textDX.h"

class TextButton : public Button
{
private:
	std::string text;
	TextDX dxFont;
	RECT drawRect; // calculated from my containing Button screen location

public:
	TextButton();
	~TextButton();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw();

	// accessors
	void calculateDrawRect();
	void setText(std::string newText) { text = newText; }
	std::string getText() { return text; }

	// override base
	bool isMouseOver();
};

