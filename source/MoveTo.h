#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to move from one position to another over time.
/// </summary>
class MoveTo : public AnimationBase
{
private:
	Vector2 m_targetPosition;
	Vector2 m_currentPosition;

public:
	/// <summary>
	/// Constructions Animation to run in seconds up to given scale and back to original over the time given.
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time to run</param>
	/// <param name="scale">Position to move to in world space</param>
	MoveTo(Image* target, float timeLimit, Vector2 moveToPos);
	void update(float deltaTime) override;
	void onSuccess() override;
};

