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
		float accumulated = 0.0f;

		for (int c = 0; c < children.size(); ++c)
		{
			float proportion = static_cast<float>(proportions[c]) / totalProportion;
			accumulated += proportion * size.y;

			int nextY = origin.y + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
			int childHeight = nextY - childYCoord;

			children[c]->setOrigin(Vector2f(origin.x, childYCoord));
			children[c]->setSize(Vector2f(size.x, static_cast<float>(childHeight)));

			childYCoord = nextY;
		}
	}
	else
	{
		int childXCoord = origin.x;
		float accumulated = 0.0f;
		for (int c = 0; c < children.size(); ++c)
		{
			float proportion = static_cast<float>(proportions[c]) / totalProportion;
			accumulated += proportion * size.x;
			int nextX = origin.x + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
			int childWidth = nextX - childXCoord;
			children[c]->setOrigin(Vector2f(childXCoord, origin.y));
			children[c]->setSize(Vector2f(static_cast<float>(childWidth), size.y));
			childXCoord = nextX;
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