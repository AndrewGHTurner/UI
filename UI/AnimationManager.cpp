#include "pch.h"
#include "AnimationManager.h"
using namespace std;


//to fix pre and post draw issues becase animations are renderred outside the recursive UI draw each animation will
//be stored with its parent branch node. When an animation is rendered the pre and post draw calls for all parent 
//nodes will be called in order from the root ... found by branch.parent.parent etc to the animation's parent branch


void AnnimationManager::addAnimation(Animation* animation) {
	animations.push_back(animation);
}
int AnnimationManager::countAnimations()
{
	return animations.size();
}
void AnnimationManager::removeAnimation(Animation* animation)
{
	animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());//Don'y you just love readable C++???
}

