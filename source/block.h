
#ifndef _BLOCK_H_                 // Prevent multiple definitions if this 
#define _BLOCK_H_                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace blockNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = 0;   // location on screen
    const int Y = 0;
    const float SPEED = 0;                // 100 pixels per second
    const float MASS = 0;// 10.0f;              // mass
    const int   TEXTURE_COLS = 2;           // texture has 2 columns
    const int   BLOCK_START_FRAME = 0;      // ball starts at frame 0
    const int   BLOCK_END_FRAME = 0;        // ball animation 
    const int   BLOCK_VALUE = 5;
}

// inherits from Entity class
class Block : public Entity
{
private:
    COLOR_ARGB color;
    BLOCK blockType;

    bool isAnimating = false;
    float originalScale;
    float animScale;

public:
    // constructors
    Block(BLOCK type = WEAK);

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void damage(WEAPON);

    // inline getters/setters
    BLOCK getBlockType() { return blockType;  }
    bool getIsAnimating() { return isAnimating; }
    void setIsAnimating(bool value) { isAnimating = value; }
    // animation callback
    void onAnimationSuccess() override;

    void setColor(COLOR_ARGB c) { color = c; };
    COLOR_ARGB getColor() { return color; };
    void setBlockColorByType();

    // animations
    void bounceScale(float initialScale, float endScale);
};
#endif

