#include "AnimationManager.h"


AnimationManager::~AnimationManager()
{
	clearAllProcesses();
}

WeakAnimationPtr AnimationManager::attachProcess(StrongAnimationPtr anim)
{
	mAnimationList.push_front(anim);
	return WeakAnimationPtr(anim);
}

unsigned int AnimationManager::updateProcesses(float deltaMs)
{
	unsigned int successCount = 0;
	unsigned int faileCount = 0;

	AnimationList::iterator it = mAnimationList.begin();

	// go thru list and update all animation processes
	while (it != mAnimationList.end()) {
		// grab the next one
		StrongAnimationPtr current = (*it);
		AnimationList::iterator thisIt = it;
		++it;

		// process is uninitiated
		if (current->getState() == AnimationBase::UNINITIATED) {
			current->init();
		}

		// running, give it some update time
		if (current->getState() == AnimationBase::RUNNING) {
			current->update(deltaMs);
		}

		if (current->isDead()) {
			switch (current->getState())
			{

			case AnimationBase::SUCCEEDED:
				// yay!
				current->onSuccess();
				++successCount;
				break;
			case AnimationBase::FAILED:
				current->onFail();
				++faileCount;
				break;
			} // end switch

			// remove animation process
			mAnimationList.erase(thisIt);
		} // end dead

	} // end while

	return ((successCount << 16 | faileCount));
}

void AnimationManager::abortAllProcesses(bool immediate)
{
	AnimationList::iterator it = mAnimationList.begin();

	// go thru list and update all animation processes
	while (it != mAnimationList.end()) {
		AnimationList::iterator tempIt = it;
		++it;

		StrongAnimationPtr pProcess = *tempIt;
		if (pProcess->isAlive())
		{
			if (immediate)
			{
				mAnimationList.erase(tempIt);
			}
		}
	}
}

void AnimationManager::clearAllProcesses()
{
	mAnimationList.clear();
}
