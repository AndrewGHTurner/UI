#include "pch.h"
#include "EvenList.h"

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

internal::EvenList::EvenList() :
	LinearListFluent() {
}
internal::EvenList::EvenList(Vector2f origin, Vector2f siz) :
	LinearListFluent(origin, siz) {
}

void internal::EvenList::setMargin(int margin)
{
	elementMargin = margin;
	notifyRecalcNeeded();
}

internal::EvenList& internal::EvenList::setChildSize(int size)
{
	childSize = size;
	notifyRecalcNeeded();
	return *this;
}

void internal::EvenList::calcPositions()
{
	float Y = this->origin.y + elementMargin;
	float X = this->origin.x + elementMargin;
	float pixelsPerWidget = this->childSize;
	if (isVertical())
	{
		if (pixelsPerWidget == -1)//calculate pixels per widget based on layout size
		{
			pixelsPerWidget = static_cast<float>(this->size.y) / children.size();
		}

		Vector2f childSize((int)this->size.x - (2 * elementMargin), pixelsPerWidget - (elementMargin));

		for (unique_ptr<TreeNode>& box : children)
		{
			Vector2f childOrigin(X, Y);

			box->setOrigin(childOrigin);
			box->setSize(childSize);
			//Y += MIN_WIDGET_HEIGHT;
			Y += pixelsPerWidget;
			if (box->hasText)
			{
				box->notifyTextChanged(true);
			}
		}
		if (pixelsPerWidget != -1)//set the size of the layout
		{
			this->size.y = (pixelsPerWidget * children.size());
		}

	}
	else//if horizontal
	{
		if (pixelsPerWidget == -1)//calculate pixels per widget based on layout size
		{
			pixelsPerWidget = static_cast<float>(this->size.x) / children.size();
		}
		Vector2f childSize(pixelsPerWidget - (elementMargin), (int)this->size.y - (2 * elementMargin));
		for (unique_ptr<TreeNode>& box : children)
		{
			Vector2f childOrigin(X, Y);
			box->setOrigin(childOrigin);
			box->setSize(childSize);
			X += pixelsPerWidget;
			if (box->hasText)
			{
				box->notifyTextChanged(true);
			}
		}
	}
	setRecalcNeededFalse();
}

UI_API EvenListPtr EvenList()
{
	return std::make_unique<internal::EvenList>();
}

