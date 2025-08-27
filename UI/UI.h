#ifndef UI_H
#define UI_H
#include "TreeNode.h"
#include "Branch.h"
#include "Leaf.h"
#include "AnimationManager.h"
#include "BehaviourManager.h"
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Page.h"
#include "UI_DLL_Interface.h"
#include <cassert>

class Page;

using namespace std;

enum ArrowDirection {
	RIGHT,
	UP,
	LEFT,
	DOWN
};

class UI;



//SHOULD PROBABLE MAKE A CONFIGURABLE UI CLASS WHICH WILL BE BUILT IN A BUILDER PATTERN AND ALLOW FOR 
//ONLY NEEDED FUNCTIONALITY TO BE CREATED VIA COMPOSITION

class UI_API UI : public Branch, public BehviourManager, public AnnimationManager {
private:
	int currentCharIndex = 0;//could make a typeing handeller class?// should probably hold this in the EText class
	unique_ptr<RenderTexture> screenTexture;//this is the texture that all UI elements will be drawn onto

	vector<reference_wrapper<const function<void()>>> leftReleaseLambdas;//hold the release lambdas on press do that the correct ones are called on release(even if a button resizes)


	UI(RenderWindow& window) : BehviourManager(), Branch(Vector2f(0, 0), Vector2f(300, 300)) {
		id = newID();//set the id of the ui element (root branch)
		if (!font.openFromFile("C:/Users/andre/Desktop/Root/utils/fonts/Terminal.ttf")) {
			cout << "font could not be loaded" << endl;
		}
		EText::window = &window;
		screenTexture = make_unique<RenderTexture>(window.getSize());
		Leaf::setTexture(screenTexture.get());
		EText::screenTexture = screenTexture.get();
	}

	static UI* instance;
public:
	static UI* initInstance(RenderWindow& window)
	{
		assert(instance == nullptr && "UI instance is reinitialized which shouldn't happen"); // Ensure instance is only created once
		instance = new UI(window);
		return instance;
	}
	/**
	*@brief Get the instance of the UI singleton
	*@note for other classes that use the UI instance a static pointer to the UI could be used to increase speed but this will produce little benefit
	
	*/
	static UI* getInstance()
	{
		assert(instance != nullptr && "UI instance is not initialized. Call initInstance first"); // Ensure instance is initialized before use
		return instance;
	}


	internal::TextBox* currentTextBox = nullptr;
	sf::Font font;
	UI(const UI&) = delete;             // disable copy constructor
	UI& operator=(const UI&) = delete;  // disable copy assignment
	UI(UI&&) noexcept = default;        // enable move constructor
	UI& operator=(UI&&) noexcept = default; // enable move assignment


	//this method will recieve all ui events and call the appropriate event handlers
	void eventDispatcher(optional<Event>& event, RenderWindow& window);

	void runUI(RenderWindow& window)
	{
		bool displayNeeded = false;
		while (std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())//can definitly fiddle with the ordering and else if these if statements to get better performamce(minute though)
			{
				window.close();
			}
			if (event->is<Event::Resized>())
			{
				auto resized = event->getIf<sf::Event::Resized>();
				if (resized) {
					//update the SFML view to match the new window size
					float width = static_cast<float>(resized->size.x);
					float height = static_cast<float>(resized->size.y);
					sf::View view(sf::FloatRect(Vector2f(0.f, 0.f), Vector2f(width, height)));
					window.setView(view);


					displayNeeded = true;

					// 2. Notify your UI system of the new size
				//	ui.updateLayout(newSize.x, newSize.y);
				}
			}

			eventDispatcher(event, window);

			if (auto textEvent = event->getIf<Event::TextEntered>())
			{
				char newChar = static_cast<char>(textEvent->unicode);
				handleTypeEvent(newChar);
			}
			if (event->getIf<Event::KeyPressed>())
			{
				auto keyEvent = event->getIf<Event::KeyPressed>();
				switch (keyEvent->code)
				{
				case Keyboard::Key::Up:
					handleArrowEvent(ArrowDirection::UP);
					break;
				case Keyboard::Key::Left:
					handleArrowEvent(ArrowDirection::LEFT);
					break;
				case Keyboard::Key::Right:
					handleArrowEvent(ArrowDirection::RIGHT);
					break;
				case Keyboard::Key::Down:
					handleArrowEvent(ArrowDirection::DOWN);
				}
			}
		}
		drawUI(window, displayNeeded);
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
			for (unique_ptr<TreeNode>& child : children)
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
			//window.clear();
			TreeNode::screenTexture->display();
			sf::Sprite sprite(TreeNode::screenTexture->getTexture());
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


	void leftDownAt(Vector2i pos);
	void leftUpAt(Vector2i pos);
	void mouseWheelScrollAt(Vector2i pos, int delta);//delta is the amount of scroll
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

	void executeRelevantLambdas(const unordered_map<int, vector<function<void()>>>& handlers, Vector2i pos)
	{
		//get a list of the boxIDs that are at position
		vector<int> boxIDs;
		getBoxesAt(pos, boxIDs, this);
		//run the lambdas from the handlers map
		for (int boxID : boxIDs)
		{
			auto it = handlers.find(boxID);
			if (it != handlers.end())//if a vector of handlers exists for this ID
			{
				for (const function<void()>& lambda : it->second)
				{
					lambda();
				}
			}
		}
	}

	vector<reference_wrapper<const function<void()>>> retrieveRelevantLambdas(const unordered_map<int, vector<function<void()>>>& handlers, Vector2i pos)
	{
		vector<reference_wrapper<const function<void()>>> relevantLambdas;
		//get a list of the boxIDs that are at position
		vector<int> boxIDs;
		getBoxesAt(pos, boxIDs, this);
		//get the lambdas from the handlers map
		for (int boxID : boxIDs)
		{
			auto it = handlers.find(boxID);
			if (it != handlers.end())//if a vector of handlers exists for this ID
			{
				for (const function<void()>& lambda : it->second)
				{
					relevantLambdas.push_back(lambda);//add the lambda to the vector
				}
			}
		}
		return relevantLambdas;
	}

	//origin - top right courner of the button
	//size - length of the button in the x and y dimensions

};


#endif
