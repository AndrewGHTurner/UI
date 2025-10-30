#include "pch.h"
#include "AnimationManager.h"
using namespace std;


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

