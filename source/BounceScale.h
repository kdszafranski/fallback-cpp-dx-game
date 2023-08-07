#pragma once
#include "AnimationBase.h"

class BounceScale : public AnimationBase
{
private:
	float endScale;
	float rate;

public:
	BounceScale(Entity* target, float scale, float time);
	void update(float ms);

};

