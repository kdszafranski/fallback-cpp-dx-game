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

private:
	State mState; // state of this animation

protected:
	float time;		// time tween takes to run
	float timer;	// timer counts up
	float elapsedTime;
	float originalScale;
	Vector2 originalPosition;
	std::shared_ptr<Entity> entity; // object to act upon

public:
	// construction
	AnimationBase(Entity* target, float t);
	~AnimationBase();

	// Interface, override in each Animation
	// called every frame from AnimationManager
	virtual void init(void) { mState = RUNNING; }
	virtual void update(float ms) = 0;
	virtual void onSuccess(void) { }
	virtual void onFail(void) { }
	virtual void animate(float deltaTime) { }


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
	float getElapsedTime() { return elapsedTime; };

private:
	void setState(State newState) { mState = newState; }

};

