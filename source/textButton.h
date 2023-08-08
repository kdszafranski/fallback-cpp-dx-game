#pragma once
#include "button.h"
#include "textDX.h"

class TextButton : public Button
{
private:
	std::string text;
	int intValue;
	int fontSize;
	TextDX displayFont;
	RECT drawRect; // calculated from my containing Button screen location

public:
	TextButton();
	~TextButton();

	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	virtual void update(float frameTime);
	virtual void draw();
	void calculateDrawRect();

	// accessors
	void setIntValue(int value) { intValue = value; }
	int getIntValue() { return intValue; }
	void setText(std::string newText) { text = newText; }
	std::string getText() { return text; }
	void setFontSize(int size) { fontSize = size; }
	int getFontSize() { return fontSize; }
	void setFontColor(COLOR_ARGB color) { displayFont.setFontColor(color); }

	// override base
	bool isMouseOver();
};

