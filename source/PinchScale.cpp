#include "PinchScale.h"

PinchScale::PinchScale(Image* target, float timeLimit, float scale)
	: AnimationBase(target, timeLimit) // initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
{
	endScale = scale;
	target->setScale(0.999f);

	rate = time / 30; // total time / 30 fps
}

void PinchScale::update(float deltaTime)
{
	if (entity) {
		timer += deltaTime;
		float const currentScale = entity->getScale();
		if (currentScale > endScale && currentScale < originalScale) {
			// go down
			entity->setScale(currentScale - rate);
		} else {
			if (currentScale > originalScale) {
				// done
				entity->setScale(originalScale);
				mState = SUCCEEDED;
			} else {
				// going up
				endScale = originalScale; // need to keep going up
				entity->setScale(currentScale + rate);
			}
		}
	}
}
