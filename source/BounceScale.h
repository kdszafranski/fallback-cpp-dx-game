#pragma once
#include "itween.h"

class BounceScale : public ITween
{
private:
	float endScale;
	float rate;

public:
	BounceScale(Entity* ent, float scale, float time);
	void update(float ms);

};

