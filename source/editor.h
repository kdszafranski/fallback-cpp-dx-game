#pragma once
#include "constants.h"
#include "textButton.h"
#include "console.h"
#include <vector>

class Editor
{
private:
	std::vector<BLOCK> blocks;
	Graphics* graphics;	// shared with Fallback
	Input* input;		// shared with Fallback
	TextButton saveButton;
	Console* console;	// shared with Fallback
	int test;

public:
	Editor();
	~Editor();
	bool initialize(Game* pGame, TextureManager* textureM, Console* pCons);

	void update();
	void draw();
	void loadEditorLevel();

	//void onLostDevice()
	//{
	//	saveButton.onLostDevice();
	//}

	//void onResetDevice()
	//{
	//	saveButton.onResetDevice();
	//}
};

