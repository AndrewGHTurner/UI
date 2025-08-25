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

ColouredButton& ColouredButton::onClick(unique_ptr<Callback> callback)
{
	UI::getInstance()->addOnClick(move(callback), rootNode->id);
	return *this;
}

ColouredButton& ColouredButton::setColor(Color c)
{
	colouredBox()->setColour(c);
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