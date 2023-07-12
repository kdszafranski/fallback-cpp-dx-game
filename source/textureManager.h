// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include "graphics.h"
#include "constants.h"

class TextureManager
{
    // TextureManager properties
  private:
    UINT       width;       // width of texture in pixels
    UINT       height;      // height of texture in pixels
    LP_TEXTURE texture;     // pointer to texture
    const char *file;       // name of file
    Graphics *graphics;     // save pointer to graphics
    bool    initialized;    // true when successfully initialized
    HRESULT hr;             // standard return type

public:
	// constructor
	TextureManager();

	// destructor
	virtual ~TextureManager();

    // Returns a pointer to the texture
    LP_TEXTURE getTexture() const {return texture;}

    // Returns the texture width
    UINT getWidth() const {return width;}

    // Return the texture height
    UINT getHeight() const {return height;}

    // Initialize the textureManager
    // Pre: *g points to Graphics object
    //      *file points to name of texture file to load
    // Post: The texture file is loaded
    virtual bool initialize(Graphics *g, const char *file);

    // Release resources
    virtual void onLostDevice();

    // Restore resourses
    virtual void onResetDevice();
};

#endif // !_TEXTURE_MANAGER_H