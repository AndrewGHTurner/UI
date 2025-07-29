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
	//store the callbacks for the release event(needed in case the click causes resize of elements)
	 
	leftReleaseCallbacks = retrieveRelevantCallbacks(leftUpCallbacks, pos);
	//run any left press callbacks associated with the position
	executeRelevantCallbacks(leftDownCallbacks, pos);
}

void UI::leftUpAt(Vector2i pos)
{
	//run the release callbacks that were stored on left down event
	for (Callback* callback : leftReleaseCallbacks)
	{
		callback->run();
	}
	leftReleaseCallbacks.clear();
}