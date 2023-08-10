#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to fade graphic alpha down to the given target over the specified amount of time (in seconds)
/// </summary>
class FadeTo : public AnimationBase
{
private:
	float m_alphaTarget;
	D3DXCOLOR m_color;

public:
	// Construction

	/// <summary>
	/// Constructs the Animation to run in seconds to given alpha (0-0.99)
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time limit</param>
	/// <param name="alphaTarget">Target alpha (0-0.99)</param>
	FadeTo(Image* target, float timeLimit, float alphaTarget);

	virtual void update(float deltaTime) override;
};

