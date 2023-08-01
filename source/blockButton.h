#pragma once
#include "constants.h"
#include "block.h"
#include "button.h"

class BlockButton : public Button
{
private:
	COLOR_ARGB color;
	BLOCK blockType;


public:
	BlockButton(BLOCK type = WEAK);
	~BlockButton();

	virtual void draw();
	void setBlockColorByType();
	void changeBlockType();
};

