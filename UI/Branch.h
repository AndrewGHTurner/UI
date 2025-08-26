#ifndef BRANCH_H
#define BRANCH_H
#include "TreeNode.h"
#include "Leaf.h"
#include <vector>
#include "TextBox.h"
#include "Facade.h"
#include "UI_DLL_Interface.h"
using namespace std;

//container for leaves and other branches
class UI_API Branch : public TreeNode {
protected:
	Color backgroundColour = Color::Transparent;

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

	void setBackgroundColour(Color colour)
	{
		backgroundColour = colour;
		setPreDrawNeededTrue();
	}	
	virtual void preDraw()
	{

		
	}

	virtual void postDraw()
	{
	}

	void draw()
	{
		if (isPreDrawNeeded())
		{
			preDraw();
		}
		for (const unique_ptr<TreeNode>& child : children)
		{
			if (child->isRedrawNeeded())
			{
				if (child->isLeaf())
				{
					static_cast<Leaf*>(child.get())->draw();
				}
				else
				{
					static_cast<Branch*>(child.get())->draw();
				}
			}
		}
		if (isPostDrawNeeded())
		{
			postDraw();
		}
		setRedrawNeededFalse();
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
	void drawText(int currentCharIndex = -1, internal::TextBox* currentTextBox = nullptr)
	{
		for (const unique_ptr<TreeNode>& child : children)
		{

			if (child->isRedrawTextNeeded())
			{
				if (child->isLeaf())
				{
					if (static_cast<internal::TextBox*>(child.get())->text)
					{
						internal::TextBox* textBox = static_cast<internal::TextBox*>(child.get());
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

	void renderBackground()
	{
		//clear the screen area covered by this layout
		RenderTexture* texture = TreeNode::screenTexture;
		VertexArray clearVertices(sf::PrimitiveType::Triangles, 6);
		//first triangle
		clearVertices[0].position = origin;
		clearVertices[1].position = Vector2f(origin.x, antiOrigin.y);
		clearVertices[2].position = Vector2f(antiOrigin.x, origin.y);
		//second triangle
		clearVertices[3].position = Vector2f(antiOrigin.x, origin.y);
		clearVertices[4].position = Vector2f(origin.x, antiOrigin.y);
		clearVertices[5].position = Vector2f(antiOrigin.x, antiOrigin.y);

		//first triangle
		clearVertices[0].color = backgroundColour;
		clearVertices[1].color = backgroundColour;
		clearVertices[2].color = backgroundColour;
		//second triangle
		clearVertices[3].color = backgroundColour;
		clearVertices[4].color = backgroundColour;
		clearVertices[5].color = backgroundColour;
		texture->draw(clearVertices);
	}

	void updateChildren()
	{
		if (backgroundColour != Color::Transparent)
		{
			renderBackground();
		}
		calcPositions();
		for (const unique_ptr<TreeNode>& child : children)
		{
			if (child->isRecalcNeeded())
			{
				if (child->isLeaf())
				{
					static_cast<Leaf*>(child.get())->updateVerticesPosition();
					internal::TextBox* b = static_cast<internal::TextBox*>(child.get());
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
