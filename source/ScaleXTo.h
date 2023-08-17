#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to scale x-axis up or down to the given target over the specified amount of time (in seconds)
/// </summary>
class ScaleXTo : public AnimationBase
{
private:
	float m_scaleTarget;
	float m_currentXScale;

public:
	// Construction

	/// <summary>
	/// Constructs the Animation to run in seconds to scale x-axis of target 
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time limit</param>
	/// <param name="targetScale">Target scale applied to x-axis</param>
	ScaleXTo(Image* target, float timeLimit, float targetScale);

	virtual void update(float deltaTime) override;
	void onSuccess() override;
};

