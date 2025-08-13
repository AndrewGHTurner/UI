#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include "Animation.h"
#include <vector>
#include "UI_DLL_Interface.h"
using namespace std;

class UI_API AnnimationManager {
private:
	vector<Animation*> animations = vector<Animation*>();
public:
	void addAnimation(Animation* animation) {
		animations.push_back(animation);
	}
	int countAnimations()
	{
		return animations.size();
	}
	void removeAnimation(Animation* animation)
	{
		animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());//Don'y you just love readable C++???
	}
	//will be called in the render loop to call the animation draw methods
	inline void runAnimations() {
		for (Animation* animation : animations)
		{
			animation->drawAnimation();//NEED TO CHECK THE RETURNED BOOL TO SEE IF THE ANIMATION HAS ENDED
		}
	}
};

#endif