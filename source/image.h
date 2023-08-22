#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "textureManager.h"
#include "constants.h"
#include "IAnimation.h"

class Image : public IAnimation
{
protected:
	Graphics* graphics;	// pointer to graphics
	TextureManager* textureManager;	// pointer to texture manager
	HRESULT hr; // standard return type

	// defined in graphics.h
	// contains details like height, width, flipped etc
	// used for Graphics::drawSprite()
	SpriteData spriteData;
	COLOR_ARGB colorFilter;
	int	frameCols;		// number of cols (1 to n) in multi-frame sprite

	// lifetime
	bool readyToDestroy;

	// frame timing
	int     startFrame;     // first frame of current animation
	int     endFrame;       // end frame of current animation
	int     currentFrame;   // current frame of animation

	// animation
	float	frameDelay;     // how long between frames of animation
	float	animTimer;      // animation timer
	bool	loop;			// true: loop frames
	bool	visible;		// true: draw it
	bool	initialized;
	bool	animComplete;	// true when loop is false and endFrame has finished

public:
	int myId;

public:
	// constructor
	Image();
	// destructor
	virtual ~Image();


	////////////////////////////////////////
	//           Getter functions         //
	////////////////////////////////////////

	// Return reference to SpriteData structure.
	const virtual SpriteData& getSpriteInfo() { return spriteData; }

	// Return visible parameter.
	virtual bool  getVisible() { return visible; }

	// Return X position.
	virtual float getX() { return spriteData.x; }

	// Return Y position.
	virtual float getY() { return spriteData.y; }

	bool canDestroy() { return readyToDestroy; }
	void setCanDestroy(bool b) { readyToDestroy = b; }

	// Return scale factor.
	virtual float getScale() { return spriteData.scale; }
	virtual float getXScale() { return spriteData.xScale; }
	virtual float getYScale() { return spriteData.yScale; }


	// Return width.
	virtual int   getWidth() { return spriteData.width; }

	// Return height.
	virtual int   getHeight() { return spriteData.height; }

	// Return center X.
	virtual float getCenterX() {
		return spriteData.x + spriteData.width / 2 * getScale();
	}

	// Return center Y.
	virtual float getCenterY() {
		return spriteData.y + spriteData.height / 2 * getScale();
	}

		// Return rotation angle in degrees.
	virtual float getDegrees() { return spriteData.angle * (180.0f / (float)PI); }

	// Return rotation angle in radians.
	virtual float getRadians() { return spriteData.angle; }

	// Return delay between frames of animation.
	virtual float getFrameDelay() { return frameDelay; }

	// Return number of starting frame.
	virtual int   getStartFrame() { return startFrame; }

	// Return number of ending frame.
	virtual int   getEndFrame() { return endFrame; }

	// Return number of current frame.
	virtual int   getCurrentFrame() { return currentFrame; }

	virtual SpriteData getSpriteData() { return spriteData; }

	// Return RECT structure of Image.
	virtual RECT  getSpriteDataRect() { return spriteData.rect; }

	// Return state of animation complete.
	virtual bool  getAnimationComplete() { return animComplete; }

	// Return colorFilter.
	virtual COLOR_ARGB getColorFilter() { return colorFilter; }

	////////////////////////////////////////
	//           Setter functions            //
	////////////////////////////////////////

	// Set X location.
	virtual void setX(float newX) { spriteData.x = newX; }

	// Set Y location.
	virtual void setY(float newY) { spriteData.y = newY; }

	virtual void setPosition(float newX, float newY)
	{
		spriteData.x = newX;
		spriteData.y = newY;
	}

	virtual void setPosition(Vector2 newPos)
	{
		spriteData.x = newPos.x;
		spriteData.y = newPos.y;
	}

	virtual void setPosition(VECTOR2 newPos)
	{
		spriteData.x = newPos.x;
		spriteData.y = newPos.y;
	}

	virtual Vector2 getPosition()
	{
		return Vector2{ spriteData.x, spriteData.y };
	}

	// Set scale to both axes
	virtual void setScale(float s) {
		spriteData.scale = s; // used for legacy purposes
		spriteData.xScale = s;
		spriteData.yScale = s;
	}
	// Set scale with differing scale on each axis
	virtual void setScale(float x, float y) {
		spriteData.xScale = x;
		spriteData.yScale = y;
	}

	// Set rotation angle in degrees.
	// 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) { spriteData.angle = deg * ((float)PI / 180.0f); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) { spriteData.angle = rad; }

	// Set visible.
	virtual void setVisible(bool v) { visible = v; }

	// Set delay between frames of animation.
	virtual void setFrameDelay(float d) { frameDelay = d; }

	// Set starting and ending frames of animation.
	virtual void setFrames(int s, int e) { startFrame = s; endFrame = e; }

	// Set current frame of animation.
	virtual void setCurrentFrame(int c);

	// Set spriteData.rect to draw currentFrame
	virtual void setRect();

	// Set spriteData.rect to r.
	virtual void setSpriteDataRect(RECT r) { spriteData.rect = r; }

	// Set animation loop. lp = true to loop.
	virtual void setLoop(bool lp) { loop = lp; }

	// Set animation complete Boolean.
	virtual void setAnimationComplete(bool a) { animComplete = a; };

	// Set color filter. (use WHITE for no change)
	virtual void setColorFilter(COLOR_ARGB color) { colorFilter = color; }

	// Set TextureManager
	virtual void setTextureManager(TextureManager* textureM)
	{
		textureManager = textureM;
	}

	////////////////////////////////////////
	//         Other functions            //
	////////////////////////////////////////

	// Allow this image/entity to do something when an animation completes
	virtual void onAnimationSuccess() { }


	// Initialize Image
	// Pre: *g = pointer to Graphics object
	//      width = width of Image in pixels  (0 = use full texture width)
	//      height = height of Image in pixels (0 = use full texture height)
	//      ncols = number of columns in texture (1 to n) (0 same as 1)
	//      *textureM = pointer to TextureManager object
	virtual bool Image::initialize(Graphics* g, int width, int height,
		int ncols, TextureManager* textureM);

	// Flip image horizontally (mirror)
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }

	// Flip image vertically
	virtual void flipVertical(bool flip) { spriteData.flipVertical = flip; }

	// Draw Image using color as filter. Default color is WHITE.
	virtual void draw(COLOR_ARGB color = 0, bool fromCenter = false);

	// Draw this image using the specified SpriteData.
	//   The current SpriteData.rect is used to select the texture.
	virtual void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter

	// Update the animation. frameTime is used to regulate the speed.
	virtual void update(float frameTime);

	D3DXCOLOR getRandomColor();

	virtual std::string toString();
};


#endif // !_IMAGE_H_
