#include "pch.h"
#include "ProportionalSpacedList.h"

internal::ProportionalSpacedList::ProportionalSpacedList() : LinearListFluent() {
}

internal::ProportionalSpacedList::ProportionalSpacedList(Vector2f origin, Vector2f siz) : LinearListFluent(origin, siz) {
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
		//don't need margin below the first element
		float proportion = static_cast<float>(proportions[0]) / totalProportion;
		accumulated += proportion * size.y;
		int nextY = origin.y + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
		int childHeight = nextY - childYCoord - (2 * elementMargin);
		children[0]->setOrigin(Vector2f(origin.x + elementMargin, childYCoord + elementMargin));
		children[0]->setSize(Vector2f(size.x - (2 * elementMargin), static_cast<float>(childHeight)));
		childYCoord = nextY;

		for (int c = 1; c < children.size(); ++c)
		{
			float proportion = static_cast<float>(proportions[c]) / totalProportion;
			accumulated += proportion * size.y;

			int nextY = origin.y + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
			int childHeight = nextY - childYCoord - elementMargin;

			children[c]->setOrigin(Vector2f(origin.x + elementMargin, childYCoord));
			children[c]->setSize(Vector2f(size.x - (2 * elementMargin), static_cast<float>(childHeight)));
			if (children[c]->hasText)
			{
				children[c]->notifyTextChanged(true);
			}
			childYCoord = nextY;
		}
	}
	else
	{
		int childXCoord = origin.x;
		float accumulated = 0.0f;
		//don't need margin to the right of first element.
		float proportion = static_cast<float>(proportions[0]) / totalProportion;
		accumulated += proportion * size.x;
		int nextX = origin.x + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
		int childWidth = nextX - childXCoord - (2 * elementMargin);
		children[0]->setOrigin(Vector2f(childXCoord + elementMargin, origin.y + elementMargin));
		children[0]->setSize(Vector2f(static_cast<float>(childWidth), size.y - (2 * elementMargin)));
		childXCoord = nextX;

		for (int c = 1; c < children.size(); ++c)
		{
			float proportion = static_cast<float>(proportions[c]) / totalProportion;
			accumulated += proportion * size.x;
			int nextX = origin.x + static_cast<int>(std::round(accumulated));//doing this distributes the floating point errors
			int childWidth = nextX - childXCoord - elementMargin;
			children[c]->setOrigin(Vector2f(childXCoord, origin.y + elementMargin));
			children[c]->setSize(Vector2f(static_cast<float>(childWidth), size.y - (2 * elementMargin)));
			if (children[c]->hasText)
			{
				children[c]->notifyTextChanged(true);
			}
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