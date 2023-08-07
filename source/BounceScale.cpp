#include "BounceScale.h"

BounceScale::BounceScale(Entity* target, float scale, float time)
{
	entity = std::make_shared<Entity>(target);
	originalScale = entity->getScale();
	originalPosition = { entity->getX(), entity->getY() };

	endScale = scale;
	time = time;

	rate = time / 30; // total time / 30 fps
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
		} else {
			// going up
			endScale = originalScale; // need to keep going up
			entity->setScale(currentScale + rate);
		}
	}
}
