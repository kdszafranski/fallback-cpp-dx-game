#pragma once
#include "AnimationBase.h"

/// <summary>
/// Tween to shrink object to given scale and then size back up to original scale.
/// </summary>
class PinchScale : public AnimationBase
{
private:
	float endScale;
	float rate;

public:
	PinchScale(Image* target, float scale, float time);
	void update(float ms);

};
