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
		auto b = make_unique<ColouredBox>(c);
		rootNode = unique_ptr<TreeNode>(move(b));
	}

	unique_ptr<TreeNode> getRootNodeOwnership() override
	{
		return move(rootNode);
	}

	ColouredBox* getRootNodePointer() override
	{
		return colouredBox();
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
		return static_cast<ColouredBox*>(rootNode.get());
    }
};

#endif