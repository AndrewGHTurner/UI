#include "pch.h"
#include "HorizontalExpanderBar.h"



void internal::HorizontalExpanderBar::add(Facade& facade, SizePolicy sizePolicy)
{
	Branch::add(facade);
	sizePolicies.resize(children.size(), sizePolicy);
	sizePolicies.back() = sizePolicy;
}

void internal::HorizontalExpanderBar::add(unique_ptr<TreeNode> child, SizePolicy sizePolicy)
{
	Branch::add(move(child));
	sizePolicies.resize(children.size(), sizePolicy);
	sizePolicies.back() = sizePolicy;
}

void internal::HorizontalExpanderBar::calcPositions()
{
	float totalFixedSize = 0;
	float numberOfExpandableChildren = 0;
	//for each child sum the fixed sizes
	for (int i = 0; i < children.size(); i++)
	{
		if (sizePolicies[i] == SizePolicy::FIXED_SIZE) {
			totalFixedSize += children[i]->getSize().x;
		}
		else if (sizePolicies[i] == SizePolicy::EXPANDER) {
			numberOfExpandableChildren++;
		}
	}
	float expandChildWidth = (size.x - totalFixedSize) / numberOfExpandableChildren;


	float buttonHeight = antiOrigin.y - origin.y;

	int leftX = origin.x;
	Vector2f buttonSize = Vector2f(0, buttonHeight);
	for (int i = 0; i < children.size(); i++)
	{
		Vector2f buttonOrigin(leftX, origin.y);
		unique_ptr<TreeNode>& child = children[i];
		child->setOrigin(buttonOrigin);

		//box->setOrigin(buttonOrigin);
		if (sizePolicies[i] == SizePolicy::FIXED_SIZE) {
			leftX += child->getSize().x;
			buttonSize.x = child->getSize().x;
		}
		else if (sizePolicies[i] == SizePolicy::EXPANDER) {
			leftX += expandChildWidth;
			buttonSize.x = expandChildWidth;
		}
		child->setSize(buttonSize);
	}

}

UI_API HorizontalExpanderBarPtr HorizontalExpanderBar()
{
	return make_unique<internal::HorizontalExpanderBar>();
}