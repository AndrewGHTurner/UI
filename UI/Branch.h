#ifndef BRANCH_H
#define BRANCH_H
#include "TreeNode.h"
#include "Leaf.h"
#include <vector>
#include "TextBox.h"
#include "Facade.h"

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
		child->notifyRecalcNeeded();
		children.push_back(move(child));
	}

	void add(Facade& facade)
	{
		unique_ptr<TreeNode> node = facade.getRootNodeOwnership();
		node->parentNode = this;
		this->add(move(node));
	}

	//remove a child by id and transfer ownership of the child to the caller
	unique_ptr<TreeNode> retrieve(int childID)
	{
		for (int i = 0; i < children.size(); ++i)
		{
			if (children[i]->id == childID)
			{
				unique_ptr<TreeNode> child = move(children[i]);
				children.erase(children.begin() + i);
				notifyRecalcNeeded();
				if (this->numTexts > 0)
				{
					notifyTextChanged(true);
				}
				return child;
			}
		}
		return nullptr;
	}
	//class UI;
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
	//	this->ui->clearID(childID); // Clear the ID from the UI's behaviour manager
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
							textBox->text.get()->draw();// currentCharIndex);
						}
						//	textBox->setCurrentCharIndex(-1);
						textBox->text.get()->draw();// -1);

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
						b->resizeText();
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
