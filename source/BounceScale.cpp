#include "BounceScale.h"

BounceScale::BounceScale(Entity* target, float scale, float t)
	: AnimationBase(target, t) // initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
{
	endScale = scale;
	target->setScale(0.999f);

	rate = t / 60; // total time / 30 fps
}

void BounceScale::update(float ms) 
{
	float const currentScale = entity->getScale();
	if (currentScale > endScale && currentScale < originalScale) {
		// go down
		entity->setScale(currentScale - rate);
	} else {
		if (currentScale > originalScale) {
			// done
			entity->setScale(originalScale);
			//mState = SUCCEEDED;
		} else {
			// going up
			endScale = originalScale; // need to keep going up
			entity->setScale(currentScale + rate);
		}
	}
}
