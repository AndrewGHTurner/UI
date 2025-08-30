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


/**
* @note Eventually logic to check that release lambdas are not in the deleted lambda cache will be needed here
*/
void UI::leftUpAt(Vector2i pos)
{
	//retrieve relevant lambdas for the position ... do not run all of these
	vector<reference_wrapper<const LambdaHolder>> relevantLambdas = retrieveRelevantLambdas(leftUpLambdas, pos);
	//for each one if it is in the leftReleaseLambdas vector then run it
	for (const reference_wrapper<const LambdaHolder> lambdaHolder : relevantLambdas)//this runs all relevant lambdas
	{
		for (auto it = leftReleaseLambdas.begin(); it != leftReleaseLambdas.end(); it++)
		{
			if (lambdaHolder.get().lambdaID == it->get().lambdaID)
			{
				it->get().lambda();
				std::swap(*it, leftReleaseLambdas.back());//place the to be removed element at the back of the vector
				leftReleaseLambdas.pop_back();//remove the back of the vector ... this is faster than erase which has O(n) complexity
				break;
			}
		}
	}
	//if not then only run it if it's id is not in the conditionalReleaseIDs set
	for (auto LambdaHolder : leftReleaseLambdas)
	{
		if (conditionalReleaseLambdaIDs.find(LambdaHolder.get().lambdaID) != conditionalReleaseLambdaIDs.end())//if the lambda is conditional
		{
			continue;//do not run it ... if it was relevant then it would have been run in the previous loop
		}
		else
		{
			LambdaHolder.get().lambda();
		}
	}
	leftReleaseLambdas.clear();
	//run all unlocalized left up lambdas
	for (const LambdaHolder& lambdaHolder : leftUpLambdasUnlocalized)
	{
		lambdaHolder.lambda();
	}
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
			for (const MouseWheelLambdaHolder& lambdaHolder : it->second)
			{
				lambdaHolder.lambda(delta);
			}
		}
	}
}

void UI::mouseMovementAt(Vector2i pos)
{
	for (const MouseMovementLambdaHolder& lambdaHolder : mouseMovementLambdas)
	{
		lambdaHolder.lambda(pos);
	}
}