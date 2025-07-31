#ifndef VERTICAL_SCROLL_H
#define VERTICAL_SCROLL_H

#include "Branch.h"
#include <SFML/OpenGL.hpp>

class Scroll : public Branch {
private:
	Vector2f scrollOffset;
	int stackHeight = 0;//this is the combined heights of all the elements in the scroll
public:
	Scroll() : Branch() {
		setPreDrawNeededTrue();
		setPostDrawNeededTrue();
	}

	void preDraw() override {
		glEnable(GL_SCISSOR_TEST);
		int flippedY = ui->getSize().y - (origin.y + size.y);
		glScissor(origin.x, flippedY, size.x, size.y);
	}

	void postDraw() override {
		glDisable(GL_SCISSOR_TEST);
	}

	void calcPositions() override {
		stackHeight = 0;
		int heightPerElement = 40; // Example height for each element
		int X = origin.x;
		int Y = origin.y + scrollOffset.y;
		for (const unique_ptr<TreeNode>& child : children)
		{
			int elmHeight = 0;
			if (child->getSize().y != 0)
			{
				elmHeight = child->getSize().y;
			}
			else
			{
				elmHeight = heightPerElement; // Default height if not set
			}


			child->setOrigin(Vector2f(X, Y));
			child->setSize(Vector2f(size.x, elmHeight));
			Y += elmHeight; // Increment Y position for the next element
			stackHeight += elmHeight;//edit this for varied height elements

		}
		setRecalcNeededFalse();
	};

	void incrementOffset(int delta) {
		scrollOffset.y += (delta * 15);
		if (scrollOffset.y > 0)
		{
			scrollOffset.y = 0; // Prevent scrolling above the top
		}
		const unique_ptr<TreeNode>& lastChild = children.back();

		if (stackHeight - size.y + scrollOffset.y < 0)
		{
			scrollOffset.y = -(stackHeight - size.y);
		}
		notifyRecalcNeeded();
	}
};

#endif