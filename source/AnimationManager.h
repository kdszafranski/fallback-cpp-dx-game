#pragma once
#include "AnimationBase.h";
#include <list>
#include <iostream>

typedef std::shared_ptr<AnimationBase> StrongAnimationPtr;
typedef std::weak_ptr<AnimationBase> WeakAnimationPtr;
typedef std::list<StrongAnimationPtr> AnimationList;

class AnimationManager
{
private:
	AnimationList mAnimationList;

public:
	// construction
	~AnimationManager(void);

	// interface
	unsigned int updateProcesses(float deltaMs);  // updates all attached processes
	WeakAnimationPtr attachProcess(StrongAnimationPtr anim);  // attaches a process to the process mgr
	void abortAllProcesses(bool immediate);

	// accessors
	unsigned int getProcessCount(void) const { return mAnimationList.size(); }
	void clearAllProcesses(void);  // should only be called by the destructor

private:
};
