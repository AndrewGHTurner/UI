#include "HorizontalProportionalSpacedBar.h"

HorizontalProportionalSpacedBar::HorizontalProportionalSpacedBar() : Branch() {
}

HorizontalProportionalSpacedBar::HorizontalProportionalSpacedBar(Vector2f origin, Vector2f siz) : Branch(origin, siz) {
}

//proportion is the amount of space the widget needs... will be relative to the proportions given to other widgets
void HorizontalProportionalSpacedBar::add(Facade& facade, int proportion)
{
	this->add(facade);
	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
}
void HorizontalProportionalSpacedBar::add(unique_ptr<TreeNode> child, int proportion)
{
	this->add(move(child));
	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
}

void HorizontalProportionalSpacedBar::calcPositions()
{
	int childXCoord = origin.x;
	for (int c = 0; c < children.size(); c++)
	{
		unique_ptr<TreeNode>& child = children[c];
		Vector2f childOrigin(childXCoord, origin.y);
		float childWidthProportion = static_cast<float>(proportions[c]) / static_cast<float>(totalProportion);
		Vector2f childSize(childWidthProportion * size.x, size.y);
		child->setOrigin(childOrigin);
		child->setSize(childSize);
		childXCoord += childSize.x;
	}
	//	setRecalcNeededFalse();
	//	setRedrawNeededTrue();
}