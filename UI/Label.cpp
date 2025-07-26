#include "Label.h"
#include "UI.h"

Label::Label(string initialText, Vector2f origin, Vector2f siz) {
	text = make_unique<EText>(ui->font, initialText);
	text->setPosition(origin);
	text->setSize(siz);

	//hasText = true;
	setRedrawTextNeededTrue();
	notifyTextChanged(true);
	updateVerticesPosition();
}

Label::Label(string initialText){
	text = make_unique<EText>(ui->font, initialText);
	//hasText = true;
	setRedrawTextNeededTrue();
	notifyTextChanged(true);
	updateVerticesPosition();
}

void Label::setColour(Color c) {
	vertices[0].color = c;
	vertices[1].color = c;
	vertices[2].color = c;
	vertices[3].color = c;
	vertices[4].color = c;
	vertices[5].color = c;
	notifyRedrawNeeded();
	notifyTextChanged(true);
}

void Label::resizeText()
{
	//if (text)
	{
		text.get()->setPosition(origin);
		text.get()->setSize(this->size);
	}
}

Color Label::getColour() {
	return vertices[0].color;
}