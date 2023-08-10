#include "AnimationBase.h"

AnimationBase::AnimationBase(Image* target, float runTime)
	: entity(target), timer(0)
{
	originalFrame = entity->getCurrentFrame();
	originalScale = entity->getScale();
	originalPosition = { entity->getX(), entity->getY() };
	time = runTime;
	mState = UNINITIATED;
}

AnimationBase::~AnimationBase()
{
	// i feel like this SHOULD be here but it causes issues
	//SAFE_DELETE(entity);
}
