#include "TreeNode.h"
#include "UI.h"

UI* TreeNode::ui = nullptr;
sf::RenderTexture* TreeNode::screenTexture = nullptr;


TreeNode::TreeNode()
{
	id = ui->newID();
}

TreeNode::TreeNode(TreeNode* parent)
{
	parentNode = parent;//this is needed for TextBox so that the text draws on ui start
	id = ui->newID();
}
TreeNode::TreeNode(Vector2f origin, Vector2f size)
{
	setOrigin(origin);
	setSize(size);
}
TreeNode::TreeNode(TreeNode* parent, Vector2f origin, Vector2f siz)
{
	id = ui->newID();
	setOrigin(origin);
	setSize(siz);
}

void TreeNode::notifyTextChanged(bool added)//bool for if text object was added or not THIS NEEDS TO BE FIXED TO ALLW FOR NOTIFICATIONS WITHOUT CHANGING STUFF
{

	if (added)
	{
		numTexts += 1;
		setRedrawTextNeededTrue();

	}
	else
	{
		numTexts -= 1;
		if (numTexts == 0)
		{
			setRedrawTextNeededFalse();
		}
	}
	if (parentNode) {
		parentNode->notifyTextChanged(added);
	}
}
//change the rendered position of the node and notify parent
void TreeNode::setOrigin(Vector2f origin)
{
	this->origin = origin;
	antiOrigin = Vector2f(origin.x + size.x, origin.y + size.y);
	notifyRecalcNeeded();
}
//change the rendered size of the node and notify parent
void TreeNode::setSize(Vector2f siz)
{
	size = siz;
	antiOrigin = Vector2f(origin.x + size.x, origin.y + size.y);
	notifyRecalcNeeded();
}
bool TreeNode::isPointWithin(Vector2i point)
{
	if (point.x > origin.x && point.y > origin.y)
	{
		if (point.x < antiOrigin.x && point.y < antiOrigin.y)
		{
			return true;
		}
	}
	return false;
}

//notify any changes in the positions of the verticies in the vertex array
//this allows vertices to be updated at most once per frame which is more efficient if adding many leaves to a layout
void TreeNode::notifyRecalcNeeded()
{
	setRecalcNeededTrue();
	//if vertices recalculation is needed then redrawing is definitely needed so might as well call it here.
	setRedrawNeededTrue();
	if (parentNode)
	{
		parentNode->notifyRecalcNeeded();
	}
}
void TreeNode::notifyRedrawNeeded()
{
	setRedrawNeededTrue();
	if (parentNode)
	{
		parentNode->notifyRedrawNeeded();
	}
}
