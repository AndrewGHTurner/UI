#ifndef HORIZONTAL_PROPORTIONAL_SPACED_BAR
#define HORIZONTAL_PROPORTIONAL_SPACED_BAR

#include "Branch.h"
#include <memory>
#include "Facade.h"

class HorizontalProportionalSpacedBar : public Branch {
private:
	vector<int> proportions;
	int totalProportion = 0;
public:
	HorizontalProportionalSpacedBar(Vector2f origin, Vector2f siz) : Branch(origin, siz) {
	}
	using Branch::add;
	//proportion is the amount of space the widget needs... will be relative to the proportions given to other widgets
	void add(Facade& facade, int proportion)
	{
		this->add(facade);
		proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
		proportions.back() = proportion;
		totalProportion += proportion;
	}
	void add(unique_ptr<TreeNode> child, int proportion)
	{
		this->add(move(child));
		proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
		proportions.back() = proportion;
		totalProportion += proportion;
	}

	void calcPositions() override
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
};

#endif