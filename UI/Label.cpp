#include "Label.h"
#include "UI.h"

Label::Label(string initialText, Vector2f origin, Vector2f siz) {
	text = make_unique<EText>(this->ui->font, initialText);
	text->setPosition(origin);
	text->setSize(siz);

	//hasText = true;
	setRedrawTextNeededTrue();
	notifyTextChanged(true);
	updateVerticesPosition();
}