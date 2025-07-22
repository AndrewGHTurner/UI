#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "EText.h"
#include "Facade.h"
#include <memory>

class TextButton : public Facade
{
private:
	unique_ptr<EText> text;
public:
	TextButton(Font& font, Vector2f origin, Vector2f size, string initialText)
	{
		text = make_unique<EText>(font, initialText);
		text->setPosition(origin);
		text->setSize(size);
	}
	TextButton& setText(string newText)
	{
		this->text->setText(newText);
		return *this;
	}
	string getText()
	{
		return this->text->getText();
	}

};


#endif