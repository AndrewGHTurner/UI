
#include "Leaf.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "EText.h"
#include "ETextContainer.h"
#include "CallBack.h"
#include "UI.h"
#include "TextBox.h"
using namespace std;


internal::TextBox::TextBox(Font& font, Vector2f origin, Vector2f siz, std::string initialText)
	: Leaf(nullptr)
{
	hasText = true;
	setRedrawTextNeededTrue();
	text = make_unique<EText>(font, initialText);
	text.get()->setPosition(origin);
	text.get()->setSize(siz);
	notifyTextChanged(true);

	updateVerticesPosition();
	//register a scroll text callback on mouse wheel event
	unique_ptr<CallBack> callback = makeScrollCallBack(scrollText, this);
	UI::getInstance()->addMouseWheelCallback(move(callback), id);
	//	ui->addAnimation(this);

	}

internal::TextBox::TextBox(string initialText)
	: Leaf(nullptr)
{
	Font& font = UI::getInstance()->font;
	hasText = true;
	setRedrawTextNeededTrue();
	text = make_unique<EText>(font, initialText);
	notifyTextChanged(true);

	updateVerticesPosition();
	//register a scroll text callback on mouse wheel event
	unique_ptr<CallBack> callback = makeScrollCallBack(scrollText, this);
	UI::getInstance()->addMouseWheelCallback(move(callback), id);
	//	ui->addAnimation(this);

}

void internal::TextBox::setCurrentCharIndex(int index)
{
	text.get()->currentCharIndex = index;
}

bool internal::TextBox::drawAnimation() {

	draw();
	text.get()->draw();
	return true;
}

void internal::TextBox::resizeText()
{
	//	if (text)
	{
		text.get()->setPosition(origin);
		text.get()->setSize(this->size);
	}
}
void internal::TextBox::setText(string newText)
{
	text.get()->setText(newText);
	notifyRedrawNeeded();
	notifyTextChanged(1);
}
string internal::TextBox::getText()
{
	return text.get()->getText();
}
void internal::TextBox::setColour(Color c)
{
	vertices[0].color = c;
	vertices[1].color = c;
	vertices[2].color = c;
	vertices[3].color = c;
	vertices[4].color = c;
	vertices[5].color = c;
}

void internal::TextBox::scrollText(tuple<TextBox*, int> param)
{
	//this is a scroll callback for a TextBox
	TextBox* textBox = static_cast<TextBox*>(std::get<0>(param));
	int delta = std::get<1>(param);
	if (UI::getInstance()->currentTextBox == textBox)
	{
		if (delta > 0)
		{
			UI::getInstance()->handleArrowEvent(ArrowDirection::UP);
		}
		else if (delta < 0)
		{
			UI::getInstance()->handleArrowEvent(ArrowDirection::DOWN);
		}

	}
}

TextBoxPtr UI_API TextBox(string initialText)
{
	return make_unique<internal::TextBox>(initialText);
}




