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
		float currentScale = entity->getScale();
		if (timer < halfTime) {
			timer += deltaTime;
			currentScale = 1.0f - clampHighLow(timer / time);
			entity->setScale(currentScale);
		} else {
			mState = SUCCEEDED;

			//entity->setScale(currentScale + deltaTime / time);
			//if (entity->getScale() > originalScale) {
			//	entity->setScale(originalScale);
			//}
		}
	}
}
