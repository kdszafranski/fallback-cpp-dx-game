#include "AnimationBase.h"

AnimationBase::AnimationBase(Entity* target, float t)
{
	entity = std::shared_ptr<Entity>(target);
	originalScale = entity->getScale();
	originalPosition = { entity->getX(), entity->getY() };
	time = t;
}

AnimationBase::~AnimationBase()
{
	
}

void AnimationBase::update(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime < time) {
		animate(deltaTime);
	} else {
		// assume it ended well
		mState = SUCCEEDED;
	}
}
