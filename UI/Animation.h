#ifndef ANIMATION_H
#define ANIMATION_H


class Animation {
public:
	virtual bool drawAnimation() = 0;
	//COULD ADD A VIRTUAL FUNCTION TO CLEAR THE ANNIMATION WHEN IT IS REMOVED FROM ANIMATIONS... EG CLEAR THE CURSOR
	virtual ~Animation() = default;
};

#endif