#pragma once
#include "AnimationBase.h"
#ifndef CLAMPHIGHLOW_H
#include "TSMath.h" 
#endif

/// <summary>
/// Tween to enlarge scale and return to original over the course of time.
/// </summary>
class PunchScale : public AnimationBase
{
private:
	bool m_punchComplete;
	float m_targetScale;
	float m_halfTime;
	float m_currentScale;

public:
	/// <summary>
	/// Constructions Animation to run in seconds up to given scale and back to original over the time given.
	/// </summary>
	/// <param name="target">Pointer to Image object</param>
	/// <param name="timeLimit">Desired time to run</param>
	/// <param name="scale">Scale target larger than original - 1.0 is graphic original, 2.0 is twice as large, etc.</param>
	PunchScale(Image* target, float timeLimit, float scale);
	void update(float ms) override;

};
