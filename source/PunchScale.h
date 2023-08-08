#pragma once
#include "AnimationBase.h"

class PunchScale : public AnimationBase
{
private:
	float endScale;
	float rate;

public:
	PunchScale(Entity* target, float scale, float time);
	void update(float ms) override;

};
