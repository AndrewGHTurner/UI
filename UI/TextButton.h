#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "EText.h"
#include "Facade.h"
#include <memory>
#include "Label.h"
#include "CallBack.h"
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
* @brief This facade is needed as it holds the colour params needed for the change colour callbacks
*/
class UI_API TextButtonMaker : public Facade
{	
public:
	//this must be a member of the page holding the buttons so that callback params are persisted and not destroyed when it goes out of scope
	TextButtonMaker()
	{
	}
	//will be called when the rootNode object is finished.... needs to handle some creation
	unique_ptr<TreeNode> getRootNodeOwnership() override
	{
		if (releasedColour.has_value())
		{
			label()->setColour(releasedColour.value()); // Set the label's colour to the released colour
		}if (pressedColour.has_value())
		{
			//add the click callbacks necessary to change the colours
			unique_ptr<LabelColour> labelColour = make_unique<LabelColour>(releasedColour.value(), label());
			
			unique_ptr<LabelColour> pressedLabelColour = make_unique<LabelColour>(pressedColour.value(), label());



			unique_ptr<CallBack> release = makeCallBack(changeColorLabel, labelColour.get());
			unique_ptr<CallBack> press = makeCallBack(changeColorLabel, pressedLabelColour.get());
			UI::getInstance()->addLeftDown(move(press), rootNode->id); // Add the callback for left down click
			UI::getInstance()->addLeftUpCallback(move(release), rootNode->id); // Add the callback for left up click
			labelColours.push_back(move(labelColour)); // Store the released colour and label for later use
			labelColours.push_back(move(pressedLabelColour)); // Store the pressed colour and label for later use
		}
		return move(rootNode);
	}

	Label* getRootNodePointer() override
	{
		return label();
	}

	TextButtonMaker& onClickLeftDown(unique_ptr<CallBack> callback)
	{
		UI::getInstance()->addOnClick(move(callback), rootNode->id);
		return *this;
	}

	TextButtonMaker& onClickLeftDown(function<void()> lambda)
	{
		UI::getInstance()->addLeftDown(lambda, rootNode->id);
		return *this;
	}

	TextButtonMaker& createButton(string initialText)
	{
		unique_ptr<Label> label = make_unique<Label>(initialText);
		rootNode = unique_ptr<TreeNode>(move(label));
		return *this;
	}

	TextButtonMaker& onClickLeftUp(unique_ptr<CallBack> callback)
	{
		UI::getInstance()->addLeftUpCallback(move(callback), rootNode->id);
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
	vector<unique_ptr<LabelColour>> labelColours = vector<unique_ptr<LabelColour>>(); //store the params for callbacks to change label colours
	optional<Color> pressedColour; // Store the pressed colour
	optional<Color> releasedColour; // Store the released colour
	Label* label()
	{
		return static_cast<Label*>(rootNode.get());
	}

	static void changeColorLabel(LabelColour* labelColour)
	{
		labelColour->label->setColour(labelColour->colour); // Set the label's colour to the stored colour
	}

};


#endif