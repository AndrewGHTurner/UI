#ifndef  UI_H
#define UI_H
#include "TreeNode.h"
#include "Branch.h"
#include "Leaf.h"
#include "AnimationManager.h"
#include "BehaviourManager.h"
#include "VerticalScroll.h"
#include <iostream>
#include "TextBox.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

enum ArrowDirection {
	RIGHT,
	UP,
	LEFT,
	DOWN
};

//SHOULD PROBABLE MAKE A CONFIGURABLE UI CLASS WHICH WILL BE BUILT IN A BUILDER PATTERN AND ALLOW FOR 
//ONLY NEEDED FUNCTIONALITY TO BE CREATED VIA COMPOSITION

class UI : public Branch, public BehviourManager, public AnnimationManager {
private:
	sf::Font font;
	TextBox* currentTextBox = nullptr;
	int currentCharIndex = 0;//could make a typeing handeller class?// should probably hold this in the EText class

public:
	UI() : BehviourManager(), Branch(Vector2f(0, 0), Vector2f(300, 300)) {
		id = newID();//set the id of the ui element (root branch)
		if (!font.openFromFile("Terminal.ttf")) {
			cout << "font could not be loaded" << endl;
		}
	}
	void drawUI(RenderWindow& const window, bool displayNeeded = false)
	{
		if (isRecalcNeeded())
		{
			//reCalc the vertices
			updateChildren();
			setRecalcNeededFalse();
		}

		//redraw the vertices 
		if (isRedrawNeeded())
		{
			displayNeeded = true;
			for (unique_ptr<TreeNode>& node : children)
			{
				if (node->isLeaf())
				{
					static_cast<Leaf*>(node.get())->draw();
				}
				else
				{
					static_cast<Branch*>(node.get())->draw();
				}
			}
			setRedrawNeededFalse();
		}

		//draw text
		if (isRedrawTextNeeded())
		{
			displayNeeded = true;
			drawText(currentCharIndex, currentTextBox);
			setRedrawTextNeededFalse();
		}


		if (countAnimations() > 0)
		{
			displayNeeded = true;
			runAnimations();
		}

		if (displayNeeded)
		{
			window.clear();
			Leaf::screenTexture->display();
			sf::Sprite sprite(Leaf::screenTexture->getTexture());
			window.draw(sprite);
			window.display();
		}

		//window.display();
	}

	void handleArrowEvent(ArrowDirection direction)
	{
		//handle for TextBox
		if (currentTextBox != nullptr)//this should go into the EText class
		{
			switch (direction)
			{
			case RIGHT:
				if (currentCharIndex < currentTextBox->getText().length())
				{
					currentCharIndex += 1;
				}
				break;
			case UP:
			{
				if (currentCharIndex == 0)
				{
					break;
				}
				string text = currentTextBox->getText();
				int indexOfPrecedingNewLine = -1;
				for (size_t i = currentCharIndex - 1; i > 0; i--) {
					if (text[i] == '\n') {
						indexOfPrecedingNewLine = i;
						break;
					}
				}
				if (indexOfPrecedingNewLine == -1)//already at the top of the document
				{
					if (text[0] == '\n')//if top line is empty
					{
						currentCharIndex = 0;
					}
					break;
				}
				int charsInFrontOfPrecedingNewLine = currentCharIndex - indexOfPrecedingNewLine;
				int indexOfNextPrecedingNewLine = -1;
				for (int i = indexOfPrecedingNewLine - 1; i > 0; i--)
				{
					if (text[i] == '\n')
					{

						indexOfNextPrecedingNewLine = i;
						break;
					}
				}
				int charsInfrontOfNewLine = currentCharIndex - indexOfPrecedingNewLine;
				if (indexOfNextPrecedingNewLine == -1)//on the second to top line of text
				{
					if (charsInfrontOfNewLine > indexOfPrecedingNewLine)
					{
						currentCharIndex = indexOfPrecedingNewLine;
					}
					else
					{
						if (text[charsInfrontOfNewLine - 1] == '\n')
						{
							currentCharIndex = charsInfrontOfNewLine;
							break;
						}
						currentCharIndex = charsInfrontOfNewLine - 1;
					}
					break;
				}
				else//in the middle of text
				{
					int charsBetweenPreviousNewLines = indexOfPrecedingNewLine - indexOfNextPrecedingNewLine;
					if (charsInfrontOfNewLine > charsBetweenPreviousNewLines)
					{
						currentCharIndex = indexOfNextPrecedingNewLine + charsBetweenPreviousNewLines;
					}
					else
					{
						currentCharIndex = indexOfNextPrecedingNewLine + charsInfrontOfNewLine;
					}
					break;
				}
				break;
			}
			case LEFT:
				if (currentCharIndex > 0)
				{
					currentCharIndex -= 1;
				}
				break;
			case DOWN:
			{
				string text = currentTextBox->getText();
				if (currentCharIndex == 0 && text[currentCharIndex] == '\n')
				{
					currentCharIndex += 1;
					break;
				}

				//find how many characters in front of the preceding newLine
				//current char index = that number infront of the next newLine
				int indexOfPrecedingNewLine = -1;
				for (int i = currentCharIndex - 1; i > 0; --i)
				{
					if (text[i] == '\n')
					{
						indexOfPrecedingNewLine = i;
						break;
					}
				}
				int charsInFrontOfNewLine = 0;
				if (indexOfPrecedingNewLine == -1)
				{
					charsInFrontOfNewLine = currentCharIndex;
				}
				else
				{
					charsInFrontOfNewLine = currentCharIndex - indexOfPrecedingNewLine;
				}
				int indexOfNextNewLine = -1;

				for (int i = currentCharIndex + 1; i < text.length(); ++i)
				{
					if (text[i] == '\n')
					{
						indexOfNextNewLine = i;
						break;
					}
				}
				if (indexOfNextNewLine == -1)//if on the bottom line
				{
					if (text[currentCharIndex] == '\n' && currentCharIndex < text.length() - 1 - charsInFrontOfNewLine)
					{
						currentCharIndex += charsInFrontOfNewLine;
					}
					else if (text[currentCharIndex] == '\n' && currentCharIndex < text.length())
					{
						currentCharIndex = text.length();
					}
					break;
				}

				if (text[currentCharIndex] == '\n')
				{
					indexOfNextNewLine = currentCharIndex;
				}
				int indexOfNextNextNewLine = -1;
				for (int i = indexOfNextNewLine + 1; i < text.length(); i++)
				{
					if (text[i] == '\n')
					{
						indexOfNextNextNewLine = i;
						break;
					}
				}
				if (indexOfNextNextNewLine == -1)//if on second to last line
				{
					int charsOfFinalLine = text.length() - indexOfNextNewLine;
					if (charsInFrontOfNewLine > charsOfFinalLine)
					{
						currentCharIndex = text.length() - 1;
					}
					else
					{
						if (indexOfPrecedingNewLine == -1)
						{
							currentCharIndex = indexOfNextNewLine + charsInFrontOfNewLine + 1;
							break;
						}
						currentCharIndex = indexOfNextNewLine + charsInFrontOfNewLine;

					}
					break;
				}
				else//in text block
				{
					int charsBetweenNextTwoNewLines = indexOfNextNextNewLine - indexOfNextNewLine;
					if (currentCharIndex == 0)//if at the start of the text
					{
						if (charsBetweenNextTwoNewLines == 0)
						{
							currentCharIndex += 1;
						}
						else
						{
							currentCharIndex = indexOfNextNewLine + 1;
						}
						break;
					}

					if (charsBetweenNextTwoNewLines == 0)
					{
						currentCharIndex += 1;
						break;
					}
					if (charsInFrontOfNewLine > charsBetweenNextTwoNewLines)
					{
						currentCharIndex = indexOfNextNewLine + charsBetweenNextTwoNewLines;
					}
					else
					{
						currentCharIndex = indexOfNextNewLine + charsInFrontOfNewLine;
						if (indexOfPrecedingNewLine == -1)
						{
							currentCharIndex += 1;
						}
					}
					break;
				}

				break;

				if (indexOfNextNewLine == 1 && indexOfPrecedingNewLine == -1)
				{
					currentCharIndex = indexOfNextNewLine + currentCharIndex;
					break;
				}
				if (indexOfPrecedingNewLine == -1)
				{
					currentCharIndex = indexOfNextNewLine + currentCharIndex;
					break;
				}
				else {
					int indexOfNextNextNewLine = -1;
					for (int i = indexOfNextNewLine + 1; i < text.length(); i++)
					{
						if (text[i] = '\n')
						{
							indexOfNextNextNewLine = i;
						}
					}
					int charsBetweenNextTwoNewLines = indexOfNextNextNewLine - indexOfNextNewLine;
					int charsInFrontOfPreviousNewLine = currentCharIndex - indexOfPrecedingNewLine;
					if (charsInFrontOfPreviousNewLine > charsBetweenNextTwoNewLines)
					{
						currentCharIndex = indexOfNextNewLine + charsBetweenNextTwoNewLines - 1;
					}
					else
					{
						currentCharIndex = indexOfNextNewLine + charsInFrontOfPreviousNewLine;
					}

				}

				break;
			}
			default:
				break;
			}
			currentTextBox->setCurrentCharIndex(currentCharIndex);
		}

	}

	void handleTypeEvent(char newChar)
	{
		if (currentTextBox != nullptr)
		{
			currentTextBox->notifyRedrawNeeded();
			string currentText = currentTextBox->getText();
			if (newChar == '\b')//backspace
			{
				if (currentCharIndex > 0)
				{
					currentText.erase(currentText.begin() + currentCharIndex - 1);
					currentTextBox->setText(currentText);

					currentCharIndex -= 1;
				}
			}
			else if (newChar == 13) {
				currentText.insert(currentText.begin() + currentCharIndex, '\n');
				currentTextBox->setText(currentText);
				currentCharIndex += 1;
			}
			else
			{
				currentText.insert(currentText.begin() + currentCharIndex, newChar);
				currentTextBox->setText(currentText);
				currentCharIndex += 1;
			}
			currentTextBox->setCurrentCharIndex(currentCharIndex);
		}
	}
	//returns the ui leaf element clicked on
	Leaf* getLeafAt(Vector2i pos, TreeNode* box)
	{
		if (box->isPointWithin(pos))
		{
			if (box->isLeaf())
			{
				return static_cast<Leaf*>(box);
			}

			if (!box->isLeaf())
			{
				// Iterate over children and return the first found leaf
				for (unique_ptr<TreeNode>& child : static_cast<Branch*>(box)->children)
				{
					Leaf* foundLeaf = getLeafAt(pos, child.get());
					if (foundLeaf)  // If a leaf is found, return it immediately
					{
						return foundLeaf;
					}
				}
			}
		}

		return nullptr; // If no leaf is found, return nullptr
	}

	/*
	I suspect that the redraw text needed and redrawneeded flags should be merged and replace one with a contains text flag
	*/


	void leftDownAt(Vector2i pos)
	{
		//detect if clicked on any textBoxes
		Leaf* leaf = getLeafAt(pos, this);
		if (leaf != nullptr && leaf->hasText)
		{
			currentTextBox = static_cast<TextBox*>(leaf);

			//COULD ADD TEXTBOX ANNIMATION HERE????
			currentCharIndex = currentTextBox->getText().length();
			currentTextBox->setCurrentCharIndex(currentCharIndex);
			addAnimation(currentTextBox);

			currentCharIndex = currentTextBox->getText().length();
		}
		else
		{
			removeAnimation(currentTextBox);
			currentTextBox = nullptr;
		}

		//call click handellers
		executeHandelers(clickHandelers, pos);
	}
	void leftUpAt();
	void hoverAt();

	void getBoxesAt(Vector2i pos, vector<int>& boxIDs, TreeNode* box)//change this to be non recursive to improve performance
	{
		if (box->isPointWithin(pos))
		{
			boxIDs.push_back(box->id);
			if (!box->isLeaf())
			{
				//may wish to add support for clickable branches????
				for (unique_ptr<TreeNode>& child : static_cast<Branch*>(box)->children) {
					getBoxesAt(pos, boxIDs, child.get());
				}
				//static_cast<Branch*>(child)->clickedAt(pos);
			}
		}
	}

	void executeHandelers(unordered_map<int, vector<Callback>> handelers, Vector2i pos)
	{
		//get a list of the boxIDs that are at position
		vector<int> boxIDs;
		getBoxesAt(pos, boxIDs, this);
		//run the callbacks from the handelers map
		for (int boxID : boxIDs)
		{
			auto it = handelers.find(boxID);
			if (it != handelers.end())//if a vector of handellers exists for this ID
			{
				for (Callback callback : it->second)
				{
					callback.run();
				}
			}
		}
	}

	void addOnClick(Callback& callback, int boxID)//wrapper name as more intuitive
	{
		addLeftDownCallback(callback, boxID);
	}

	//origin - top right courner of the button
	//size - length of the button in the x and y dimensions

	unique_ptr<TextBox> addButton(Vector2f origin, Vector2f size, string initialText)
	{
		unique_ptr<TextBox> newButton = make_unique<TextBox>(font, origin, size, initialText);

		return newButton;
	}
	VerticalScroll* makeVerticalScroll(Vector2f origin, Vector2f size) {
		VerticalScroll* newVerticalScroll = new VerticalScroll(this, origin, size);
		return newVerticalScroll;
	}
};
#endif
