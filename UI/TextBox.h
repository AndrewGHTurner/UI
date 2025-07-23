#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "Leaf.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "Animation.h"
#include "EText.h"

using namespace std;

class TextBox : public Leaf, public Animation {

public:
	std::optional<std::unique_ptr<EText>> text;
	TextBox(Font& font, Vector2f origin, Vector2f siz, string initialText)
		: Leaf(nullptr)
	{
		hasText = true;
		setRedrawTextNeededTrue();
		text = make_unique<EText>(font, initialText);
		(*text).get()->setPosition(origin);
		(*text).get()->setSize(siz);
		notifyTextChanged(true);

		updateVerticesPosition();
		//	ui->addAnimation(this);

	}

	void setCurrentCharIndex(int index)
	{
		text->get()->currentCharIndex = index;
	}

	bool drawAnimation() override {

		draw();
		text->get()->draw();
		return true;
	}

	TextBox(const TextBox&) = delete;  // Prevent copying

	void r()
	{
		if (text)
		{
			(*text)->setPosition(origin);
			(*text)->setSize(this->size);
		}
	}
	void setText(string newText)
	{
		(*text)->setText(newText);
		notifyRedrawNeeded();
		notifyTextChanged(1);
	}
	string getText()
	{
		return (*text)->getText();
	}
	void setColour(Color c)
	{
		vertices[0].color = c;
		vertices[1].color = c;
		vertices[2].color = c;
		vertices[3].color = c;
		vertices[4].color = c;
		vertices[5].color = c;
	}

};


#endif