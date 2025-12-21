#include "pch.h"
#include "UI.h"

void UI::leftDownAt(Vector2i pos)
{
	//remove old text box animation if it exists
	if (currentTextBox != nullptr)
	{
		removeAnimation(currentTextBox);
		currentTextBox = nullptr;
		currentCharIndex = -2;
	}
	//detect if clicked on any textBoxes
	Leaf* leaf = getLeafAt(pos, this);
	if (leaf != nullptr && leaf->hasText)
	{
		if (static_cast<internal::TextBox*>(leaf)->isEditable())
		{
			currentTextBox = static_cast<internal::TextBox*>(leaf);

			currentCharIndex = currentTextBox->getText().length();
			currentTextBox->setCurrentCharIndex(currentCharIndex);
			addAnimation(currentTextBox, leaf);

			currentCharIndex = currentTextBox->getText().length();
		}
	}
	//store the lambdas for the release event(needed in case the click causes resize of elements)
	leftReleaseLambdas = retrieveRelevantLambdas(EventType::LEFT_CLICK_UP, pos);
	//run any left press lambdas associated with the position
	if (leaf != nullptr)
	{
		raiseEvent(EventType::LEFT_CLICK_DOWN, leaf->id, pos);
	}
	raiseEvent(EventType::LEFT_CLICK_DOWN, globalEventBoxID, pos);//raise global left down event
}


/**
* @note Eventually logic to check that release lambdas are not in the deleted lambda cache will be needed here
*/
void UI::leftUpAt(Vector2i pos)
{
	EventData data;
	data.mousePosition = pos;
	//retrieve relevant lambdas for the position ... do not run all of these
	vector<reference_wrapper<const EventCallback>> relevantLambdas = retrieveRelevantLambdas(EventType::LEFT_CLICK_UP, pos);
	//for each one if it is in the leftReleaseLambdas vector then run it
	for (const reference_wrapper<const EventCallback> lambdaHolder : relevantLambdas)//this runs all relevant lambdas
	{
		for (auto it = leftReleaseLambdas.begin(); it != leftReleaseLambdas.end(); it++)
		{
			if (lambdaHolder.get().lambdaID == it->get().lambdaID)
			{
				it->get().lambda(data);
				std::swap(*it, leftReleaseLambdas.back());//place the to be removed element at the back of the vector
				leftReleaseLambdas.pop_back();//remove the back of the vector ... this is faster than erase which has O(n) complexity
				break;
			}
		}
	}
	//if not then only run it if it's id is not in the conditionalReleaseIDs set
	for (auto LambdaHolder : leftReleaseLambdas)
	{
		if (currentPage->registry.conditionalReleaseLambdaIDs.find(LambdaHolder.get().lambdaID) != currentPage->registry.conditionalReleaseLambdaIDs.end())//if the lambda is conditional
		{
			continue;//do not run it ... if it was relevant then it would have been run in the previous loop
		}
		else
		{
			LambdaHolder.get().lambda(data);
		}
	}
	leftReleaseLambdas.clear();
	//run all unlocalized left up lambdas
	raiseEvent(EventType::LEFT_CLICK_UP, globalEventBoxID);
}

void UI::mouseWheelScrollAt(Vector2i pos, int deltag)
{

	vector<int> boxIDs;
	getBoxesAt(pos, boxIDs, this);
	//handle the scroll event
	for (int boxID : boxIDs)
	{
		raiseEvent(EventType::MOUSE_WHEEL, boxID, pos, deltag);
	}
	raiseEvent(EventType::MOUSE_WHEEL, globalEventBoxID, pos, deltag);//raise global mouse wheel event
}

void UI::mouseMovementAt(Vector2i pos)
{
	EventKey key(EventType::HOVER_MOVE, globalEventBoxID);
	const auto it = currentPage->registry.callbackMap.find(key);
	EventData data;
	data.mousePosition = pos;
	if (it != currentPage->registry.callbackMap.end())//if a vector of handlers exists for this ID
	{
		for (const EventCallback& lambdaHolder : it->second)
		{
			lambdaHolder.lambda(data);
		}
	}

	//record the currently hovered elements
	vector<int> boxIDs;
	unordered_set<uint32_t> newlyHoveredElementIDs;
	getBoxesAt(pos, boxIDs, this);
	for (int boxID : boxIDs)
	{
		newlyHoveredElementIDs.insert(boxID);
	}
	//run hover handlers for currently hovered elements

	//TODO

	//run hover enter calbacks for newly hovered elements

	for (int boxID : boxIDs)
	{
		if (currentPage->registry.hoveredElementIDs.find(boxID) == currentPage->registry.hoveredElementIDs.end())//if this element was not previously hovered
		{
			//run hover enter callback for this element
			EventKey key(EventType::HOVER_ENTER, boxID);
			const auto it = currentPage->registry.callbackMap.find(key);
			if (it != currentPage->registry.callbackMap.end())
			{
				for (auto& lambdaHolder : it->second)
				{
					lambdaHolder.lambda(data);
				}
			}
		}
	}

	//run hover exit callbacks for elements no longer hovered

	for (uint32_t hoveredElementID : currentPage->registry.hoveredElementIDs)
	{
		if (newlyHoveredElementIDs.find(hoveredElementID) == newlyHoveredElementIDs.end())//if this element is no longer hovered
		{
			//run hover exit callback for this element
			EventKey key(EventType::HOVER_EXIT, hoveredElementID);
			const auto it = currentPage->registry.callbackMap.find(key);
			if (it != currentPage->registry.callbackMap.end()) {
				for (auto& lambdaHolder : it->second)
				{
					lambdaHolder.lambda(data);
				}
			}
		}
	}
	
	currentPage->registry.hoveredElementIDs = move(newlyHoveredElementIDs);
}