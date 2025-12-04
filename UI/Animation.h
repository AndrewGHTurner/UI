#ifndef ANIMATION_H
#define ANIMATION_H

#include "UI_DLL_Interface.h"
class UI_API Animation {
public:
	virtual bool drawAnimation() = 0;

	/**
	* @brief called when the animation is removed from the animation manager
	*/
	virtual bool removeAnimation() = 0;
	//COULD ADD A VIRTUAL FUNCTION TO CLEAR THE ANNIMATION WHEN IT IS REMOVED FROM ANIMATIONS... EG CLEAR THE CURSOR
	virtual ~Animation() = default;
};

#endif