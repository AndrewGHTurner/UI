#include "pch.h"
#include "StaticList.h"

internal::StaticList::StaticList() : LinearListFluent()
{
}

void internal::StaticList::calcPositions()
{
	Vector2f currentOrigin = origin;
	for (const unique_ptr<TreeNode>& child : children)
	{
		child->setOrigin(currentOrigin);
		if (isVertical())
		{
			currentOrigin.y += child->getSize().y;
		}
		else
		{
			currentOrigin.x += child->getSize().x;
		}
	}



}

StaticListPtr StaticList()
{
	return make_unique<internal::StaticList>();
}