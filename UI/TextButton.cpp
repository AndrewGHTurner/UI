#include "TextButton.h"
#include "UI.h"
internal::TextButton::TextButton(string text) : Label(text)
{
}

internal::TextButton& internal::TextButton::onClickLeftDown(function<void()> lambda)
{
	UI::getInstance()->addLeftDown(lambda, this->id);
	return *this;
}

internal::TextButton& internal::TextButton::onClickLeftDown(function<void()> lambda, int& lambdaID)
{
	lambdaID = UI::getInstance()->addLeftDown(lambda, this->id);
	return *this;
}

internal::TextButton& internal::TextButton::onClickLeftUp(function<void()> lambda, bool allowSlideOff)
{
	UI::getInstance()->addLeftUp(lambda, this->id, allowSlideOff);
	return *this;
}

internal::TextButton& internal::TextButton::setColour(Color c)
{
	releasedColour = c; // Store the released colour
	Label::setColour(c); // Set the initial colour
	return *this;
}
/**
	@note This method will break if called twice ... fixing this is a future me problem 
*/
internal::TextButton& internal::TextButton::setPressedColour(Color c)
{
	pressedColour = c; // Store the pressed colour

	if (pressedColour != Color::Transparent)
	{
		function<void()> changeColourRelease = [this]() {
			this->Label::setColour(this->releasedColour);
			};

		function<void()> changeColourPress = [this]() {
			this->Label::setColour(this->pressedColour);
			};

		UI::getInstance()->addLeftDown(changeColourPress, this->id); // Add the lambda for left down click
		UI::getInstance()->addLeftUp(changeColourRelease, this->id); // Add the lambda for left up click
	}

	return *this;
}

TextButtonPtr TextButton(string text) {
	return make_unique<internal::TextButton>(text);
}