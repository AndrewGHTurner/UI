#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include "Animation.h"
#include <vector>

class UI_API AnnimationManager {
private:
	std::vector<Animation*> animations = std::vector<Animation*>();
public:
	void addAnimation(Animation* animation);
	int countAnimations();
	void removeAnimation(Animation* animation);
	//will be called in the render loop to call the animation draw methods
	inline void runAnimations() {
		for (Animation* animation : animations)
		{
			animation->drawAnimation();//NEED TO CHECK THE RETURNED BOOL TO SEE IF THE ANIMATION HAS ENDED
		}
	}
};

#endif