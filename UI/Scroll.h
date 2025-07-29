#ifndef VERTICAL_SCROLL_H
#define VERTICAL_SCROLL_H

#include "Branch.h"

class Scroll : public Branch {
private:
	Vector2f scrollOffset;
public:
	Scroll() : Branch() {
	}

	void calcPositions() override {
		//find the list of visible rows

		//for each row get the list of visible elements

		//position the visible elements to be drawn
	};



};

#endif