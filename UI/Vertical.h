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

using VerticalPtr = std::unique_ptr<class _Vertical>;

class UI_API _Vertical : public Branch {
private:
    int elementMargin = 0;
    vector<TreeNode*> contents;



public:
    _Vertical();
    _Vertical(Vector2f origin, Vector2f siz);
    void setMargin(int margin);
    void calcPositions();
};

// Free function factory
UI_API VerticalPtr Vertical();


#endif