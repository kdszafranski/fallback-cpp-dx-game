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
	const int   TEXTURE_COLS = 4; 
}

class PowerUp : public Entity
{
private:
	POWERUP type;

public:
	PowerUp(POWERUP pType);

	// inherited
	virtual void draw();
	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);
	void update(float frameTime);

	// other
	void setFrameByType();
};


#endif