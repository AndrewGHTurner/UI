#include "pch.h"
#include "Label.h"
#include "UI.h"

internal::Label::Label(string initialText, Vector2f origin, Vector2f siz) {
	text = make_unique<EText>(UI::getInstance()->font, initialText);
	text->setPosition(origin);
	text->setSize(siz);

	//hasText = true;
	setRedrawTextNeededTrue();
	notifyTextChanged(true);
	updateVerticesPosition();
}

internal::Label::Label(string initialText){
	text = make_unique<EText>(UI::getInstance()->font, initialText);
	//hasText = true;
	setRedrawTextNeededTrue();
	notifyTextChanged(true);
	updateVerticesPosition();
}

void internal::Label::setColour(Color c) {
	vertices[0].color = c;
	vertices[1].color = c;
	vertices[2].color = c;
	vertices[3].color = c;
	vertices[4].color = c;
	vertices[5].color = c;
	notifyRedrawNeeded();
	notifyTextChanged(true);
}

void internal::Label::setTextJustification(TextJustification justification) {
	text.get()->setTextJustification(justification);
	notifyRedrawNeeded();
	notifyTextChanged(true);
}

TextJustification internal::Label::getTextJustification() {
	return text.get()->getJustification();
}

void internal::Label::resizeText()
{
	//if (text)
	{
		text.get()->setPosition(origin);
		text.get()->setSize(size);
	}
}

void internal::Label::setText(string newText) {
	text.get()->setText(newText);
	notifyRedrawNeeded();
	notifyTextChanged(true);
}

Color internal::Label::getColour() {
	return vertices[0].color;
}

LabelPtr Label(string initialText) {
	return make_unique<internal::Label>(initialText);
}