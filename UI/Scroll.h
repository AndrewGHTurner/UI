#ifndef VERTICAL_SCROLL_H
#define VERTICAL_SCROLL_H

#include "Branch.h"
#include <SFML/OpenGL.hpp>
#include "UI_DLL_Interface.h"
#include "UI.h"

class UI_API Scroll : public Branch {
private:
	Vector2f scrollOffset;
	int stackHeight = 0;//this is the combined heights of all the elements in the scroll
public:
	Scroll();

	void preDraw() override;

	void postDraw() override;

	void calcPositions() override;

	void incrementOffset(int delta);
};

#endif