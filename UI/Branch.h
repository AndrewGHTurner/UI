#ifndef BRANCH_H
#define BRANCH_H
#include "TreeNode.h"
#include "Leaf.h"
#include <vector>
#include "TextBox.h"


using namespace std;

//container for leaves and other branches
class Branch : public TreeNode {
public:
	Branch() {
		setIsLeafFalse();
	}


	Branch(Vector2f origin, Vector2f siz) : TreeNode(origin, siz)
	{
		setIsLeafFalse();
	}
	Branch(TreeNode* container, Vector2f origin, Vector2f siz) : TreeNode(container, origin, siz)
	{
		setIsLeafFalse();
	}
	void draw()
	{
		for (const unique_ptr<TreeNode>& child : children)
		{
			if (child->isLeaf())
			{
				if (child->isRedrawNeeded())
				{
					static_cast<Leaf*>(child.get())->draw();
				}
			}
			else
			{
				static_cast<Branch*>(child.get())->draw();
			}
		}
		setRecalcNeededFalse();
	}



	//one vector is better as uses less memory than leaf vector + branch vector and a single vector maintains ordering
	//needs NodeType flag
	vector<unique_ptr<TreeNode>> children;
	void add(unique_ptr<TreeNode> child)
	{
		child->parentNode = this;
		if (child->isRedrawTextNeeded())
		{
			notifyTextChanged(true);
		}
		children.push_back(move(child));
		notifyRecalcNeeded();
	}

	void remove(int childID)
	{
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			if ((*it)->id == childID)
			{
				children.erase(it);
				notifyRecalcNeeded();
				if (this->numTexts > 0)
				{
					notifyTextChanged(true);
				}
				return;
			}
		}
	}

	virtual void calcPositions() {};
	void drawText(int currentCharIndex = -1, TextBox* currentTextBox = nullptr)
	{
		for (const unique_ptr<TreeNode>& child : children)
		{

			if (child->isRedrawTextNeeded())
			{
				if (child->isLeaf())
				{
					if (static_cast<TextBox*>(child.get())->text)
					{
						TextBox* textBox = static_cast<TextBox*>(child.get());
						if (textBox == currentTextBox)
						{
							textBox->setRedrawTextNeededFalse();
							//		textBox->setCurrentCharIndex(currentCharIndex);
							textBox->text->get()->draw();// currentCharIndex);
						}
						//	textBox->setCurrentCharIndex(-1);
						textBox->text->get()->draw();// -1);

					}

				}
				else
				{
					static_cast<Branch*>(child.get())->drawText(currentCharIndex, currentTextBox);
				}
			}
		}
		setRedrawTextNeededFalse();
	}
	void updateChildren()
	{
		calcPositions();
		for (const unique_ptr<TreeNode>& child : children)
		{
			if (child->isRecalcNeeded())
			{
				if (child->isLeaf())
				{
					static_cast<Leaf*>(child.get())->updateVerticesPosition();
					TextBox* b = static_cast<TextBox*>(child.get());
					if (b->isRedrawTextNeeded())
					{
						b->r();
					}
				}
				else
				{
					static_cast<Branch*>(child.get())->updateChildren();
				}
			}
		}
		setRecalcNeededFalse();
	}
};

#endif // !BRANCH_H
