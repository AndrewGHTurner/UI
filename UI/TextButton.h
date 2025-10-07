#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "Label.h"
#include <functional>

namespace internal{
	class UI_API TextButton : public internal::Label
	{
	public:
		TextButton(string text);
		internal::TextButton& setText(string newText);
		TextButton& onClickLeftDown(function<void()> lambda);

		TextButton& onClickLeftDown(function<void()> lambda, int& lambdaID);

		TextButton& onClickLeftUp(function<void()> lambda, bool allowSlideOff = false);

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