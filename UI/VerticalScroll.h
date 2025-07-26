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
	int elementMargin = 0; // Margin between elements in the scroll
	vector<TreeNode*> contents;
public:
	VerticalScroll() :
		Branch() {
	}
	VerticalScroll(Vector2f origin, Vector2f siz) :
		Branch(origin, siz) {
	}

	void setMargin(int margin)
	{
		elementMargin = margin;
		notifyRecalcNeeded();
	}

	void calcPositions() override
	{
		if (elementMargin > 0)
		{
			//clear the screen area covered by this layout
			RenderTexture* texture = Leaf::screenTexture;
			VertexArray clearVertices(sf::PrimitiveType::Triangles, 6);
			//first triangle
			clearVertices[0].position = origin;
			clearVertices[1].position = Vector2f(origin.x, antiOrigin.y);
			clearVertices[2].position = Vector2f(antiOrigin.x, origin.y);
			//second triangle
			clearVertices[3].position = Vector2f(antiOrigin.x, origin.y);
			clearVertices[4].position = Vector2f(origin.x, antiOrigin.y);
			clearVertices[5].position = Vector2f(antiOrigin.x, antiOrigin.y);

			//first triangle
			clearVertices[0].color = Color::Black;
			clearVertices[1].color = Color::Black;
			clearVertices[2].color = Color::Black;
			//second triangle
			clearVertices[3].color = Color::Black;
			clearVertices[4].color = Color::Black;
			clearVertices[5].color = Color::Black;
			texture->draw(clearVertices);
		}

		float heightPerWidget = static_cast<float>(this->size.y) / children.size();
		//Vector2f childSize(this->size.x, MIN_WIDGET_HEIGHT);
		Vector2f childSize((int)this->size.x - (2 * elementMargin), heightPerWidget - (elementMargin));
		float Y = this->origin.y + elementMargin;
		float X = this->origin.x + elementMargin;
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