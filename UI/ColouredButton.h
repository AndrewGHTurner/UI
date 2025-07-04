#ifndef COLOURED_BUTTON_H
#define COLOURED_BUTTON_H

#include "ColouredBox.h"
#include "CallBack.h"
#include "ui.h"
#include "Facade.h"
#include <memory>
using namespace std;

class ColouredButton : public Facade
{
private:

public:
	ColouredButton(Color c)
	{
		rootNode = new ColouredBox(c);//potential memory leak if not moved to a unique_ptr
	}

	ColouredBox* getRootNode() override
	{
		return static_cast<ColouredBox*>(rootNode);
	}

	ColouredButton& onClick(unique_ptr<Callback> callback, UI& ui)
	{
		ui.addOnClick(move(callback), rootNode->id);
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