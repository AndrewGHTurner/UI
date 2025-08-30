#ifndef HORIZONTAL_SPACED_BAR
#define HORIZONTAL_SPACED_BAR
#include "Branch.h"
#include <memory>
#include "UI_DLL_Interface.h"
#include "SizePolicy.h"


/**
* @brief A horizontal layout that holds a size policy for each of its children
*/
class UI_API HorizontalExpanderBar : public Branch {
private:
	vector<uint8_t> sizePolicies;
public:
	HorizontalExpanderBar(Vector2f origin, Vector2f siz) : Branch(origin, siz) {
		
	}

	void add(Facade& facade, SizePolicy sizePolicy)
	{
		Branch::add(facade);
		sizePolicies.resize(children.size(), sizePolicy);
		sizePolicies.back() = sizePolicy;
	}

	void add(unique_ptr<TreeNode> child, SizePolicy sizePolicy)
	{
		Branch::add(move(child));
		sizePolicies.resize(children.size(), sizePolicy);
		sizePolicies.back() = sizePolicy;
	}

	void calcPositions() override
	{
		int totalFixedSize = 0;
		int numberOfExpandableChildren = 0;
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
		int expandChildWidth = (size.x - totalFixedSize) / numberOfExpandableChildren;


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
};

#endif