#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to shrink object to given scale and then size back up to original scale.
/// </summary>
class PinchScale : public AnimationBase
{
private:
	bool m_pinchComplete;
	float m_targetScale;
	float m_halfTime;
	float m_currentScale;

public:
	/// <summary>
	/// Pinch the scale down and back over the course of the given time.
	/// </summary>
	/// <param name="target">Image object to act upon</param>
	/// <param name="timeLimit">Time to run animation</param>
	/// <param name="scale">Desired scale that is smaller than starting scale</param>
	PinchScale(Image* target, float timeLimit, float scale);
	void update(float ms);
	void onSuccess() override;

};
