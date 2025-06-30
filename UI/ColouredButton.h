#ifndef COLOURED_BUTTON_H
#define COLOURED_BUTTON_H

#include "ColouredBox.h"
#include "CallBack.h"
#include "ui.h"
#include "Facade.h"

class ColouredButton : public Facade
{
public:

	ColouredButton(Color c)
	{
		rootNode = new ColouredBox(c);
	}

	ColouredButton& onClick(Callback callback, UI& ui)
	{
		ui.addOnClick(callback, rootNode->id);
		return *this;
	}

	ColouredButton& setColor(Color c)
	{
		colouredBox()->setColour(c);
		return *this;
	}

	Color getColor()
	{
		return colouredBox()->colour;
	}

	int getID()
	{
		return rootNode->id;
	}
private:
	inline ColouredBox* colouredBox()
	{
		return static_cast<ColouredBox*>(rootNode);
	}
};

#endif