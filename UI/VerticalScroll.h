#ifndef VERTICAL_SCROLL_H
#define VERTICAL_SCROLL_H

#define MIN_WIDGET_HEIGHT 40.0

#include "Branch.h"
#include "Facade.h"
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

class VerticalScroll : public Branch {
private:
	vector<TreeNode*> contents;
public:
	VerticalScroll() :
		Branch() {
	}
	VerticalScroll(Vector2f origin, Vector2f siz) :
		Branch(origin, siz) {
	}
	void calcPositions() override
	{
		float heightPerWidget = static_cast<float>(this->size.y) / children.size();
		//Vector2f childSize(this->size.x, MIN_WIDGET_HEIGHT);
		Vector2f childSize(this->size.x, heightPerWidget);
		float Y = this->origin.y;
		float X = this->origin.x;
		for (unique_ptr<TreeNode>& box : children)
		{
			Vector2f childOrigin(X, Y);

			box->setOrigin(childOrigin);
			box->setSize(childSize);
			//Y += MIN_WIDGET_HEIGHT;
			Y += heightPerWidget;
			if (box->hasText)
			{
				box->notifyTextChanged(true);
			}	
		}
		setRecalcNeededFalse();
	}
};

#endif