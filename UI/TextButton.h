#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "LabelFluent.h"
#include "InteractiveFluent.h"
#include <functional>

namespace internal{
	class UI_API TextButton : public InteractiveFluent<TextButton, LabelFluent<TextButton>>
	{
	public:

		using InteractiveFluent<TextButton, LabelFluent<TextButton>>::InteractiveFluent;//inherit constructors
	//	TextButton(string text);
		TextButton& setText(string newText);

		TextButton& setColour(Color c);

		TextButton& setPressedColour(Color c);
	private:
		Color pressedColour = Color::Transparent; // Store the pressed colour
		Color releasedColour = Color::Transparent; // Store the released colour
	};
}
using TextButtonPtr = std::unique_ptr<class internal::TextButton>;

TextButtonPtr UI_API TextButton(string labelText);
#endif