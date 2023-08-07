#pragma once

#include "constants.h"
#include "entity.h"
#include <memory>

/// <summary>
/// Base Interface for Animations/Tweens
/// </summary>
class ITween
{
protected:
	float time; // time tween takes to run
	float elapsedTime;
	float timer;	// timer counts up
	float originalScale;
	Vector2 originalPosition;
	std::shared_ptr<Entity> entity; // object to act upon
	
public:
	ITween();
	virtual ~ITween() = 0;
	virtual void update(float ms) = 0;

	void setTime(float t) { time = t; }
};

