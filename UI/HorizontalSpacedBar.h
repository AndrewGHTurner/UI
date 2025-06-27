#ifndef HORIZONTAL_SPACED_BAR
#define HORIZONTAL_SPACED_BAR
#include "Branch.h"
#include <memory>

//PLAN FOR VERTICAL/HORIZONTAL SCROLLABLE LIST VIEW
/*
each widget has an origin and a size.
the list view will contain a list of widgets and a list of widgets currently in view.
only the widgets currently in view will update the vertex array. The others will have their vertices zeroed.
on scroll the list viewer will check if there is space for another widget. If there is then it will get another one from it's
list and place it into the widget's in view list.
the widgets in view will have a scroll offset

ALTERNATIVELY
the scroller could maintain a virtual position for each widget and check if the widget is in view when renderring?
*/
class HorizontalSpacedBar : public Branch {
private:

public:
	HorizontalSpacedBar(Vector2f origin, Vector2f siz, TreeNode* container) : Branch(container, origin, siz) {
		
	}

	void calcPositions() override
	{
		float buttonWidth = size.x / children.size();
		float buttonHeight = antiOrigin.y - origin.y;
		Vector2f buttonSize(buttonWidth, buttonHeight);
		int leftX = origin.x;
		for (unique_ptr<TreeNode>& box : children)
		{
			Vector2f buttonOrigin(leftX, origin.y);
			box->setOrigin(buttonOrigin);
			box->setSize(buttonSize);


			leftX += buttonWidth;
		}

	}
};

#endif