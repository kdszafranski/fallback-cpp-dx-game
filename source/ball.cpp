// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "ball.h"

//=============================================================================
// default constructor
//=============================================================================
Ball::Ball() : Entity()
{
	spriteData.width = ballNS::WIDTH;           // size of Ball
	spriteData.height = ballNS::HEIGHT;
	spriteData.x = ballNS::X;                   // location on screen
	spriteData.y = ballNS::Y;

	// set bounding box for BOX collider
	collisionType = entityNS::BOX;      // override's Image default to CIRCLE
	edge.top = -ballNS::HEIGHT / 2;     // -8
	edge.right = ballNS::WIDTH / 2;     // 8
	edge.bottom = ballNS::HEIGHT / 2;   // 8
	edge.left = -ballNS::WIDTH / 2;     // -8

	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = 1;
	currentSpeed = ballNS::SPEED;   // starting speed

	startFrame = ballNS::BALL_START_FRAME;     // first frame of ship animation
	endFrame = ballNS::BALL_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;

	radius = ballNS::WIDTH / 2.0;
	mass = ballNS::MASS;

	collisionType = entityNS::BOX;
}


//=============================================================================
// Initialize the Ball.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ball::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ball
//=============================================================================
void Ball::draw()
{
	Image::draw();              // draw ball
}

//=============================================================================
// apply the given power up
//=============================================================================
void Ball::applyPowerUp(POWERUP type)
{
	// apply relevant power up
	if (type == ZOOM) {
		// if we're going slow, let's really speed up
		if (currentSpeed < ballNS::SPEED) {
			currentSpeed = ballNS::SPEED;
			currentSpeed *= 1.5;
		}
	}
	if (type == SLOW) {
		// slow our speed
		currentSpeed *= 0.5;
	}
}

//=============================================================================
// remove power ups
//=============================================================================
void Ball::removePowerUp()
{
	currentSpeed = ballNS::SPEED;
}

void Ball::bumpSpeedUp()
{
	currentSpeed += 0.15f;
}

void Ball::launch()
{
	// restart my stuff
	setVelocity({ 0, -90 }); // straight up
	removePowerUp();
	activate();
}

//=============================================================================
// Ball bounces off a BOX collider entity (really just the Blocks, ship is handled separately)
//=============================================================================
void Ball::bounce(VECTOR2& collisionVector, SpriteData otherSpriteData, int& dir)
{
	const float myX = getX();
	const float myY = getY();
	// total right-edge x position of other entity
	const float boxWidth = (otherSpriteData.x + otherSpriteData.width);
	// total bottom y position of other entity
	const float boxHeight = (otherSpriteData.y + otherSpriteData.height);

	const D3DXVECTOR2* myCenter = getCenter();
	// set dir with direction of collision
	// 1 top, 2 right, 3 bottom, 4 left

	// left
	// determine more above or more below
	if (myX < otherSpriteData.x)
	{
		// top left
		if (myY <= otherSpriteData.y)
		{
			// now, where specifically is the ball?
			// more to the side than above
			if (myCenter->y >= otherSpriteData.y) {
				dir = 4;
				flipX();
				return;
			}

			// more above
			flipY();
			dir = 1;
			return;
		}

		// bottom left
		if (myY >= boxHeight) {
			dir = 3;
			flipY();
			return;
		}

		if (velocity.x == 0) {
			// going straight up, hitting bottom right
			flipY();
			dir = 3;
			return;
		}

		// just left
		dir = 4;
		flipX();
		return;
	}

	// right of top-left corner... needs more specifics
	if (myX > otherSpriteData.x) {

		// top
		if (myY < otherSpriteData.y) {
			if (myCenter->y > otherSpriteData.y) {
				// right, toward the top
				dir = 2;
				flipX();
				return;
			}

			if (velocity.y < 0 && velocity.x < 0) {
				// negative
				dir = 2;
				flipX();
				return;
			}

			// on top
			dir = 1;
			flipY();
			return;
		}

		// bottom
		if (myY > boxHeight - 2)
		{
			if (myCenter->x > boxWidth) { // -1?
				// more right
				if (velocity.x == 0) {
					// going straight up, hit bottom right
					dir = 3;
					flipY();
					return;
				}

				// let's look closer
				if (myX > boxWidth) {
					// more right
					dir = 2;
					flipX();
					return;
				} else {
					// a bit bottom
					dir = 3;
					flipY();
					return;
				}
			} else {
				// more bottom
				dir = 3;
				flipY();
				return;
			}
		}

		// just to the right
		dir = 2;
		flipX();
	}

}


/// <summary>
/// Allows basic left, normal, right aiming based on where the ball hits
/// Still uses constant 250 y velocity
/// </summary> 
/// <param name="collisionVector"></param>
/// <param name="collisionPosition"></param>
/// <param name="otherSpriteData"></param>
void Ball::bounceOffShip(VECTOR2& collisionVector, VECTOR2& collisionPosition, SpriteData otherSpriteData)
{
	// determine WHERE along the ship we hit
	const float myX = getCenterX();
	const float myY = getY();
	const float middleX = otherSpriteData.width / 3.0f; // middle third of ship
	const float rightX = middleX * 2; // right-hand third of ship

	// get ship-relative position from ship's origin (x = 0)
	collisionPosition.x = myX - otherSpriteData.x;
	collisionPosition.y = myY - otherSpriteData.y;

	if (collisionPosition.x < middleX) {
		// left-hand side, aim left
		velocity.y = -velocity.y;
		velocity.x = -110;
	} else if (collisionPosition.x > middleX && collisionPosition.x < rightX) {
		// middle, just reflect upish
		velocity.y = -velocity.y;
		velocity.x *= 0.5; // reducing the x angle by half
	} else {
		// right third, aim right
		velocity.y = -velocity.y;
		velocity.x = 110;
	}

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ball::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x * currentSpeed;         // move along X 
	spriteData.y += frameTime * velocity.y * currentSpeed;         // move along Y

	// Bounce off walls
	// NOT done with actual collisions, this is done strictly from screen position
	if (spriteData.x > GAME_WIDTH - ballNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - ballNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
		audio->playCue(CLICK);
	} else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
		audio->playCue(CLICK);
	}

	if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
		audio->playCue(CLICK);
	}
}

//=============================================================================
// damage
//=============================================================================
void Ball::damage(WEAPON weapon)
{
}


