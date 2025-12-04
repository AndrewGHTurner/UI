#include "pch.h"
#include "AnimationManager.h"
using namespace std;


//to fix pre and post draw issues becase animations are renderred outside the recursive UI draw each animation will
//be stored with its parent branch node. When an animation is rendered the pre and post draw calls for all parent 
//nodes will be called in order from the root ... found by branch.parent.parent etc to the animation's parent branch


void AnnimationManager::runPreDraws(Branch* branch) {
	if (branch->parentNode != nullptr) {
		runPreDraws(static_cast<Branch*>(branch->parentNode));
	}
	if (branch->isPreDrawNeeded()) {
		branch->preDraw();
	}
}

void AnnimationManager::runPostDraws(Branch* branch) {
	if (branch->isPostDrawNeeded()) {
		branch->postDraw();
	}
	if (branch->parentNode != nullptr) {
		runPostDraws(static_cast<Branch*>(branch->parentNode));
	}
}

void AnnimationManager::addAnimation(Animation* animation, Leaf* leaf) {
	animations.push_back(make_tuple(animation, leaf));
}
int AnnimationManager::countAnimations()
{
	return animations.size();
}
void AnnimationManager::removeAnimation(Animation* animation)
{
	animation->removeAnimation();
	animations.erase(
		std::remove_if(
			animations.begin(), animations.end(),
			[&](auto& entry) { return std::get<0>(entry) == animation; }
		),
		animations.end()
	);
}

