#include "UI.h"

void UI::leftDownAt(Vector2i pos)
{
	//detect if clicked on any textBoxes
	Leaf* leaf = getLeafAt(pos, this);
	if (leaf != nullptr && leaf->hasText)
	{
		currentTextBox = static_cast<internal::TextBox*>(leaf);

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
	//store the lambdas for the release event(needed in case the click causes resize of elements)

	leftReleaseLambdas = retrieveRelevantLambdas(leftUpLambdas, pos);
	//run any left press lambdas associated with the position
	executeRelevantLambdas(leftDownLambdas, pos);
}

void UI::leftUpAt(Vector2i pos)
{
	//run the release lambdas that were stored on left down event
	for (reference_wrapper<const function<void()>> lambda : leftReleaseLambdas)
	{
		lambda();
	}
	leftReleaseLambdas.clear();
}

void UI::mouseWheelScrollAt(Vector2i pos, int delta)
{
	vector<int> boxIDs;
	getBoxesAt(pos, boxIDs, this);
	//handle the scroll event
	for (int boxID : boxIDs)
	{
		auto it = mouseWheelLambdas.find(boxID);
		if (it != mouseWheelLambdas.end())//if a vector of handlers exists for this ID
		{
			for (const function<void(int delta)>& lambda : it->second)
			{
				lambda(delta);
			}
		}
	}
}