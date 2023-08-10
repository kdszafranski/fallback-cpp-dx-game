#pragma once
#include "entity.h"
#include <memory>

/// <summary>
/// Represents a base Animation Process, managed by an AnimationManager.
/// </summary>
class AnimationBase
{
	friend class AnimationManager;

public:
	enum State {
		UNINITIATED = 0,	// created but not running
		RUNNING,			// running each frame
		PAUSED,
		SUCCEEDED,			// completed successfully
		FAILED,				// failed to complete
	};

protected:
	State mState; // state of this animation
	int originalFrame;
	float time;		// time tween takes to run
	float timer;	// timer counts up
	float originalScale;
	Vector2 originalPosition;
	Image* entity; // object to act upon

public:
	// construction
	AnimationBase(Image* target, float time);
	~AnimationBase();

	// Interface, override in each Animation
	// called every frame from AnimationManager
	virtual void init(void) { mState = RUNNING; }
	virtual void update(float deltaTime) = 0;
	virtual void onSuccess(void) { }
	virtual void onFail(void) { }


	// Functions for ending the process.
	inline void Succeed(void);
	inline void Fail(void);

	// pause
	inline void Pause(void);
	inline void UnPause(void);

	// accessors
	State getState(void) const { return mState; }
	bool isAlive(void) const { return (mState == RUNNING || mState == PAUSED); }
	bool isDead(void) const { return (mState == SUCCEEDED || mState == FAILED); }
	bool isPaused(void) const { return mState == PAUSED; }

	// Accessors
	// sets overall run time
	void setTime(float t) { time = t; };
	// gets run time
	float getTime() { return time; };
	// gets elapsed time
	float getElapsedTime() { return timer; };

	float clampHighLow(float x)
	{
		if (x < 0) x = 0.0f;
		if (x > 1) x = 1.0f;
		return x;
	}

	float clampToLow(float t, float low)
	{
		if (t < low) t = low;
		if (t > 1) t = 1.0f;
		return t;
	}

	float lerp(float a, float b, float f)
	{
		return a * (1.0 - f) + (b * f);
	}

private:
	void setState(State newState) { mState = newState; }

};
