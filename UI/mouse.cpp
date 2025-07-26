#include "UI.h"

void UI::leftDownAt(Vector2i pos)
{
	//detect if clicked on any textBoxes
	Leaf* leaf = getLeafAt(pos, this);
	prevPressAt = pos; // Store the node that was pressed on for later release callbacks
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
	//THERE IS A BUG THAT WHEN YOU CLICK A BUTTON, IF THAT BUTTON CHANGES SHAPE SUCH THAT IT LEAVES THE CLICK POS, THE RELEVANT LEFT UP CALLGACKS
	//ARE NEVER CALLED. TO SOLVE THIS WE NEED TO HOLD A VECTOR OF RELEVANT CALLBACKS WHICH WILL NEED TO BE GATHERED HERE AND USED WHEN LEFT UP EVENT
	//OCCURES. AT THE MOMENT THIS IS A SMALL BUG SO I WILL NOT BOTHER


	//run any left press callbacks associated with the position
	executeRelevantCallbacks(leftDownCallbacks, pos);
}

void UI::leftUpAt(Vector2i pos)
{
	//run any release callbacks of the 
	//run any left up callbacks associated with the position
	executeRelevantCallbacks(leftUpCallbacks, prevPressAt);
}