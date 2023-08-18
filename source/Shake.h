#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to vigorously shake the target on x and y axes
/// </summary>
class Shake : public AnimationBase
{
private:
	Vector2 m_movementBounds;
	Vector2 m_currentPosition;

public:
	/// <summary>
	/// Constructions Animation to run in seconds up to jump the target to a new position each frame.
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time to run</param>
	/// <param name="scale">Distance allowed to shake</param>
	Shake(Image* target, float timeLimit, Vector2 moveBounds);
	void update(float deltaTime) override;
	void onSuccess() override;
};

