#pragma once
#include "constants.h"
#include "block.h"
#include "button.h"

class BlockButton : public Button
{
private:
	bool isSelected;
	COLOR_ARGB color;
	BLOCK blockType;

public:
	BlockButton(BLOCK type = WEAK, bool selected = false);
	~BlockButton();
	BLOCK getBlockType() { return blockType; }

	virtual void draw(bool fromCenter = false);
	void setBlockColorByType();
	void changeBlockType(BLOCK type);
	void setSelected(bool sel) { isSelected = sel; }
};

