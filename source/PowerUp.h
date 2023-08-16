#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "entity.h"
#include "constants.h"

namespace powerupNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = 0;   // starting location on screen
	const int Y = 0;
	const float SPEED = 80;                // 
	const float MASS = 0; // 10.0f;              // mass
	const int   TEXTURE_COLS = 8; 
}

class PowerUp : public Entity
{
private:
	POWERUP type;
	COLOR_ARGB color;
	Image diamond;


public:
	PowerUp(POWERUP pType, VECTOR2 position);

	// inherited
	virtual void draw();
	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* powerupTexture);
	void update(float frameTime);

	// other
	void setFrameByType();
	POWERUP getPowerUpType() { return type; }
	COLOR_ARGB getColor() { return color; }
};


#endif