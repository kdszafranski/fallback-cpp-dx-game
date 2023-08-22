#pragma once
#include "AnimationBase.h"
#ifndef CLAMPHIGHLOW_H
#include "TSMath.h" 
#endif

/// <summary>
/// Tween to enlarge scale and return to original over the course of time.
/// </summary>
class DirectionBounce : public AnimationBase
{
private:
	bool m_moveComplete;
	float m_halfTime;
	Vector2 m_targetPosition;
	Vector2 m_currentPosition;

public:
	/// <summary>
	/// Constructions Animation to run in seconds up to given scale and back to original over the time given.
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time to run</param>
	/// <param name="scale">Postion to move to in world space</param>
	DirectionBounce(Image* target, float timeLimit, Vector2 moveToPos);
	void update(float deltaTime) override;
	void onSuccess() override;

};
