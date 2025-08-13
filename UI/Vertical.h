#ifndef VERTICAL_H
#define VERTICAL_H

#define MIN_WIDGET_HEIGHT 40.0
#include "UI_DLL_Interface.h"
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

class UI_API Vertical : public Branch {
private:
	int elementMargin = 0; // Margin between elements in the scroll
	vector<TreeNode*> contents;
public:
	Vertical();
	Vertical(Vector2f origin, Vector2f siz);

	void setMargin(int margin);

	void calcPositions() override;
};

#endif