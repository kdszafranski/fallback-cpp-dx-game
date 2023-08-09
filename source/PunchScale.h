#pragma once
#include "AnimationBase.h"

class PunchScale : public AnimationBase
{
private:
	float endScale;
	float rate;

public:
	PunchScale(Image* target, float scale, float time);
	void update(float ms) override;

};
