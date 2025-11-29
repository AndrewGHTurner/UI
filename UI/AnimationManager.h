#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include "Animation.h"
#include <vector>
#include <tuple>

class Leaf;



class UI_API AnnimationManager {
private:
	std::vector<std::tuple<Animation*, Leaf*>> animations = std::vector<tuple<Animation*, Leaf*>>();
	//recursive function to run pre draws from root to leaf
	void runPreDraws(Branch* branch);
	//recursive function to run post draws from leaf to root
	void runPostDraws(Branch* branch);
public:
	void addAnimation(Animation* animation, Leaf*);
	int countAnimations();
	void removeAnimation(Animation* animation);
	//will be called in the render loop to call the animation draw methods
	inline void runAnimations() {
		for (const tuple<Animation*, Leaf*>& animation : animations)
		{
			Animation* anim = std::get<0>(animation);
			Leaf* leaf = std::get<1>(animation);
			runPreDraws(static_cast<Branch*>(leaf->parentNode));
			anim->drawAnimation();
			runPostDraws(static_cast<Branch*>(leaf->parentNode));
		}
	}
};

#endif