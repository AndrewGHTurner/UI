#include "pch.h"
#include "ColouredButton.h"

ColouredButton::ColouredButton(Color c)
{
	auto b = make_unique<ColouredBox>(c);
	rootNode = unique_ptr<TreeNode>(move(b));
}

unique_ptr<TreeNode> ColouredButton::getRootNodeOwnership()
{
	return move(rootNode);
}

ColouredBox* ColouredButton::getRootNodePointer()
{
	return colouredBox();
}

ColouredButton& ColouredButton::onClick(function<void(EventData d)> lambda)
{
	UI::getInstance()->addLeftDown(lambda, rootNode->id);
	return *this;
}

ColouredButton& ColouredButton::setColor(Color c)
{
	colouredBox()->setColour(c);
	return *this;
}

ColouredButton& ColouredButton::setSize(Vector2f siz)
{
	colouredBox()->setSize(siz);
	return *this;
}

Color ColouredButton::getColor()
{
	return colouredBox()->colour;
}

int ColouredButton::getID()
{
	return rootNode->id;
}