
#ifndef _BALL_H_                 // Prevent multiple definitions if this 
#define _BALL_H_                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ballNS
{
    const int WIDTH = 16;                   // image width
    const int HEIGHT = 16;                  // image height
    const int X = 10;   // location on screen
    const int Y = 10;
    const float SPEED = 300;                // 100 pixels per second
    const float MASS = 0;// 10.0f;              // mass
    const int   TEXTURE_COLS = 1;           // texture has 8 columns
    const int   BALL_START_FRAME = 0;      // ball starts at frame 0
    const int   BALL_END_FRAME = 0;        // ball animation 
}

// inherits from Entity class
class Ball : public Entity
{
private:

public:
    // constructor
    Ball();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void update(float frameTime);
    void damage(WEAPON);
};
#endif

