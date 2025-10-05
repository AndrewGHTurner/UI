#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "EText.h"
#include "Facade.h"
#include <memory>
#include "Label.h"
#include "UI.h"
#include "TreeNode.h"
#include <vector>
#include <functional>
#include "UI_DLL_Interface.h"
using namespace std;

struct UI_API LabelColour {
	Color colour = Color::Black;
	Label* label = nullptr;
	LabelColour(Color colour, Label* label) : colour(colour), label(label) {}
	LabelColour() = default; // Default constructor for empty initialization
};
/**
* @brief This facade is used to provide a nice API for creating text buttons
*/
class UI_API TextButtonMaker : public Facade
{
public:
	TextButtonMaker()
	{
	}
	//will be called when the rootNode object is finished.... needs to handle some creation
	unique_ptr<TreeNode> getRootNodeOwnership() override
	{

		label()->setColour(releasedColour); // Set the label's colour to the released colour

		if (pressedColour != Color::Transparent)
		{
			function<void()> changeColourRelease = [l = rootNode.get(),colour = releasedColour]() {
				static_cast<Label*>(l)->setColour(colour);
				};

			function<void()> changeColourPress = [l = rootNode.get(), colour = pressedColour]() {
				static_cast<Label*>(l)->setColour(colour);
				};

			UI::getInstance()->addLeftDown(changeColourPress, rootNode->id); // Add the lambda for left down click
			UI::getInstance()->addLeftUp(changeColourRelease, rootNode->id); // Add the lambda for left up click
		}
		return move(rootNode);
	}



	Label* getRootNodePointer() override
	{
		return label();
	}

	TextButtonMaker& onClickLeftDown(function<void()> lambda)
	{
		UI::getInstance()->addLeftDown(lambda, rootNode->id);
		return *this;
	}

	TextButtonMaker& onClickLeftDown(function<void()> lambda, int &lambdaID)
	{
		lambdaID = UI::getInstance()->addLeftDown(lambda, rootNode->id);
		return *this;
	}

	TextButtonMaker& createButton(string initialText)
	{
		unique_ptr<Label> label = make_unique<Label>(initialText);
		releasedColour = Color::Transparent;
		pressedColour = Color::Transparent;
		rootNode = unique_ptr<TreeNode>(move(label));
		return *this;
	}

	TextButtonMaker& onClickLeftUp(function<void()> lambda, bool allowSlideOff = false)
	{
		UI::getInstance()->addLeftUp(lambda, rootNode->id, allowSlideOff);
		return *this;
	}

	TextButtonMaker& setColour(Color c)
	{
		releasedColour = c; // Store the released colour
		return *this;
	}

	TextButtonMaker& setPressedColour(Color c)
	{
		pressedColour = c; // Store the pressed colour
		return *this;
	}

	//TextButtonMaker& setText(string newText)
	//{
	//	//this->text->setText(newText);
	//	//return *this;
	//}
	//string getText()
	//{
	//	return this->text->getText();
	//}
private:
	Color pressedColour = Color::Transparent; // Store the pressed colour
	Color releasedColour = Color::Transparent; // Store the released colour
	Label* label()
	{
		return static_cast<Label*>(rootNode.get());
	}

};


#endif