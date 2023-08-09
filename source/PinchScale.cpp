#include "PinchScale.h"

PinchScale::PinchScale(Image* target, float timeLimit, float scale)
	: AnimationBase(target, timeLimit) // initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
{
	pinchComplete = false;
	targetScale = scale;
	halfTime = time / 2;
	rate = time / 30; // total time / 30 fps
}

void PinchScale::update(float deltaTime)
{
	if (entity) {
		float const currentScale = entity->getScale();

		timer += deltaTime;
		if (timer < halfTime) {
			// go down for half the time
			entity->setScale(currentScale - deltaTime / (time * 2));
		} else {
			entity->setScale(currentScale + deltaTime / (time * 2));
			if (entity->getScale() > originalScale) {
				entity->setScale(originalScale);
				mState = SUCCEEDED;
			}
		}
	}
}
