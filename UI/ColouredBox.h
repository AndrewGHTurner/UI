#ifndef COLOURED_BOX_H
#define COLOURED_BOX_H
#include "Leaf.h"
#include "UI_DLL_Interface.h"
class UI_API ColouredBox : public Leaf
{
public:
	Color colour;
	ColouredBox() : Leaf(nullptr)
	{ 
	
	}
	ColouredBox(Color c) : Leaf(nullptr)
	{
		setColour(c);
	}

	ColouredBox(Color c, TreeNode* container)
		: Leaf(container)
	{
		setColour(c);
	}
	void setColour(Color c)
	{
		colour = c;
		vertices[0].color = c;
		vertices[1].color = c;
		vertices[2].color = c;
		//second triangle
		vertices[3].color = c;
		vertices[4].color = c;
		vertices[5].color = c;
		notifyRedrawNeeded();
	}
};

#endif // COLOURED_BOX_H
