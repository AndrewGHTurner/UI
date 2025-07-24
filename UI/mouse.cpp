#include "UI.h"

void UI::leftDownAt(Vector2i pos)
{
	//detect if clicked on any textBoxes
	Leaf* leaf = getLeafAt(pos, this);
	if (leaf != nullptr && leaf->hasText)
	{
		currentTextBox = static_cast<TextBox*>(leaf);

		currentCharIndex = currentTextBox->getText().length();
		currentTextBox->setCurrentCharIndex(currentCharIndex);
		addAnimation(currentTextBox);

		currentCharIndex = currentTextBox->getText().length();
	}
	else
	{
		removeAnimation(currentTextBox);
		currentTextBox = nullptr;
	}
	//run any left press callbacks associated with the position
	executeRelevantCallbacks(leftDownCallbacks, pos);
}

void UI::leftUpAt(Vector2i pos)
{
	//run any left up callbacks associated with the position
	executeRelevantCallbacks(leftUpCallbacks, pos);
}