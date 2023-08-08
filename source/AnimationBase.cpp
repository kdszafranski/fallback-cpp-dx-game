#include "AnimationBase.h"

AnimationBase::AnimationBase(Entity* target, float t)
	: entity(target)
{
	originalScale = entity->getScale();
	originalPosition = { entity->getX(), entity->getY() };
	time = t;
	mState = UNINITIATED;
}

AnimationBase::~AnimationBase()
{
	// i feel like this SHOULD be here but it causes issues
	//SAFE_DELETE(entity);
}
