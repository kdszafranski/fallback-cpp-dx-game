#pragma once
#include "AnimationBase.h";
#include <list>

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
	unsigned int updateProcesses(unsigned long deltaMs);  // updates all attached processes
	WeakAnimationPtr attachProcess(StrongAnimationPtr anim);  // attaches a process to the process mgr
	//void abortAllProcesses(bool immediate);

	// accessors
	unsigned int getProcessCount(void) const { return mAnimationList.size(); }

private:
	void clearAllProcesses(void);  // should only be called by the destructor
};

