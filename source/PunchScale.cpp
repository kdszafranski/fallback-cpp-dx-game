#include "PunchScale.h"

PunchScale::PunchScale(Image* target, float timeLimit, float scale)
	: AnimationBase(target, timeLimit) // initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
{
	endScale = scale;
	target->setScale(1.001f);

	rate = time / 30; // total time / 30 fps
}

/// <summary>
/// Scales up and returns to normal
/// </summary>
/// <param name="ms"></param>
void PunchScale::update(float ms)
{
	if (entity) {
		float const currentScale = entity->getScale();
		if (currentScale < endScale && currentScale > originalScale) {
			// go up
			entity->setScale(currentScale + rate);
		} else {
			if (currentScale < originalScale) {
				// done
				entity->setScale(originalScale);
				mState = SUCCEEDED;
			} else {
				// going down
				endScale = originalScale; // need to keep going down
				entity->setScale(currentScale - rate);
			}
		}
	}
}
