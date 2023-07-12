// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "textureManager.h"

//=============================================================================
// Constructor
//=============================================================================
TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;  // set true when successfully initialized
}

//=============================================================================
// Destructor
//=============================================================================
TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}


//=============================================================================
// Loads the texture file from disk
// Parameters: pointers to graphics object and filename
// Post: returns true if successful, false if failed
//=============================================================================
bool TextureManager::initialize(Graphics *g, const char *f)
{
	try {
		graphics = g;	// the graphics object
		file = f;		// the texture file

		// width, height both passed in by ref to our private variables
		// texture is filled with the texture data
		hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);

		if (FAILED(hr)) {
			SAFE_RELEASE(texture);
			return false;
		}
	}
	catch (...) { 
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in TextureManager::init"));
		return false; 
	}

	// all cool, texture loaded
	initialized = true;

	return true;
}

//=============================================================================
// Called when graphics device is lost
//=============================================================================
void TextureManager::onLostDevice()
{
    if (!initialized)
        return;
    SAFE_RELEASE(texture);
}

//=============================================================================
// called when graphics device is reset
//=============================================================================
void TextureManager::onResetDevice()
{
    if (!initialized)
        return;
    graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}

