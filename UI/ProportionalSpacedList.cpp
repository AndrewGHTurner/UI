#include "pch.h"
#include "ProportionalSpacedList.h"

internal::ProportionalSpacedList::ProportionalSpacedList() : ListLayout() {
}

internal::ProportionalSpacedList::ProportionalSpacedList(Vector2f origin, Vector2f siz) : ListLayout(origin, siz) {
}

//proportion is the amount of space the widget needs... will be relative to the proportions given to other widgets
void internal::ProportionalSpacedList::add(Facade& facade, int proportion)
{
	this->add(facade);
	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
}
void internal::ProportionalSpacedList::add(unique_ptr<TreeNode> child, int proportion)
{
	this->add(move(child));
	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
}

/**
* @note could factor this algorithm out as horizontal splitter also uses it
*/
void internal::ProportionalSpacedList::calcPositions()
{
	if (isVertical())
	{
		int childYCoord = origin.y;
		for (int c = 0; c < children.size(); c++)
		{
			unique_ptr<TreeNode>& child = children[c];
			Vector2f childOrigin(origin.x, childYCoord);
			float childHeightProportion = static_cast<float>(proportions[c]) / static_cast<float>(totalProportion);
			Vector2f childSize(size.x, childHeightProportion * size.y);
			child->setOrigin(childOrigin);
			child->setSize(childSize);
			childYCoord += childSize.y;
		}
	}
	else
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
	}
	//	setRecalcNeededFalse();
	//	setRedrawNeededTrue();
}

ProportionalSpacedListPtr ProportionalSpacedList() {
	return make_unique<internal::ProportionalSpacedList>();
}
ProportionalSpacedListPtr ProportionalSpacedList(Vector2f origin, Vector2f siz) {
	return make_unique<internal::ProportionalSpacedList>(origin, siz);
}