#include "pch.h"
#include "InputController.h"
#include "EventType.h"

uint32_t InputController::insertCallback(EventType type, const function<void()>& lambda, int boxID)
{
	EventKey key(type, boxID);
	uint32_t lambdaID = UI::getInstance()->newID();
	auto& callbackVector = callbackMap[key]; // creates empty vector if needed
	callbackVector.emplace_back(LambdaHolder(lambdaID, lambda));
	return lambdaID;
}

uint32_t InputController::insertCallback(EventType type, const function<void(int)>& lambda, int boxID)
{
	EventKey key(type, boxID);
	uint32_t lambdaID = UI::getInstance()->newID();
	auto& callbackVector = callbackMap[key]; // creates empty vector if needed
	callbackVector.emplace_back(LambdaHolder(lambdaID, lambda));
	return lambdaID;
}

uint32_t InputController::insertCallback(EventType type, const function<void(Vector2i)>& lambda, int boxID)
{
	EventKey key(type, boxID);
	uint32_t lambdaID = UI::getInstance()->newID();
	auto& callbackVector = callbackMap[key]; // creates empty vector if needed
	callbackVector.emplace_back(LambdaHolder(lambdaID, lambda));
	return lambdaID;
}

uint32_t InputController::addLeftDown(function<void()> lambda, int boxID)
{
	return insertCallback(EventType::LEFT_CLICK_DOWN, lambda, boxID);
}

uint32_t InputController::addLeftUp(function<void()> lambda, int boxID, bool allowSlideOff)
{
	uint32_t lambdaID = insertCallback(EventType::LEFT_CLICK_UP, lambda, boxID);
	//record if this lambda is conditional
	if (allowSlideOff)
	{
		conditionalReleaseLambdaIDs.insert(lambdaID);
	}
	return lambdaID;
}

uint32_t InputController::addLeftUp(function<void()> lambda)
{
	return insertCallback(EventType::LEFT_CLICK_UP, lambda, globalEventBoxID);
}

uint32_t InputController::addMouseWheelLambda(function<void(int)> lambda, int boxID)
{
	return insertCallback(EventType::MOUSE_WHEEL, lambda, boxID);
}

uint32_t InputController::addMouseMovementLambda(function<void(Vector2i)> lambda)
{
	return insertCallback(EventType::HOVER_MOVE, lambda, globalEventBoxID);
}

uint32_t InputController::addHoverEnterLambda(function<void(Vector2i mousePosition)> lambda, int boxID)
{
	return insertCallback(EventType::HOVER_ENTER, lambda, boxID);
}

uint32_t InputController::addHoverExitLambda(function<void(Vector2i mousePosition)> lambda, int boxID)
{
	return insertCallback(EventType::HOVER_EXIT, lambda, boxID);
}

uint32_t InputController::addKeyPressLambda(function<void()> lambda, int keyCode)
{
	return insertCallback(EventType::KEY_PRESS, lambda, keyCode);
}



void InputController::removeHoverExitLambda(uint32_t boxID, uint32_t lambdaID) {
	EventKey key(EventType::HOVER_EXIT, boxID);
	const auto& it = callbackMap.find(key);
	if (it != callbackMap.end()) {
		vector<LambdaHolder>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				break; // Exit after removing the first matching lambda
			}
		}
	}
}

void InputController::removeMouseMovementLambda(uint32_t lambdaID) {
	EventKey key(EventType::HOVER_MOVE, globalEventBoxID);
	const auto& it = callbackMap.find(key);
	if (it != callbackMap.end()) {
		vector<LambdaHolder>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				break; // Exit after removing the first matching lambda
			}
		}
	}
}

void InputController::removeLeftUp(uint32_t lambdaID) {
	EventKey key(EventType::LEFT_CLICK_UP, globalEventBoxID);
	const auto& it = callbackMap.find(key);
	if (it != callbackMap.end()) {
		vector<LambdaHolder>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				break; // Exit after removing the first matching lambda
			}
		}
	}
}

void InputController::removeLeftDown(uint32_t lambdaID, uint32_t boxID) {
	EventKey key(EventType::LEFT_CLICK_DOWN, boxID);
	const auto& it = callbackMap.find(key);
	if (it != callbackMap.end()) {
		vector<LambdaHolder>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				break; // Exit after removing the first matching lambda
			}
		}
	}
}

void InputController::removeAllLambdasForElement(int boxID) {
	EventKey keysToRemove[] = {
		EventKey(EventType::LEFT_CLICK_DOWN, boxID),
		EventKey(EventType::LEFT_CLICK_UP, boxID),
		EventKey(EventType::MOUSE_WHEEL, boxID),
		EventKey(EventType::HOVER_MOVE, boxID),
		EventKey(EventType::HOVER_ENTER, boxID),
		EventKey(EventType::HOVER_EXIT, boxID)
	};
	for (const EventKey& key : keysToRemove) {
		callbackMap.erase(key);
	}
}

void InputController::executeHoverEnterLambdas(int elementID)
{
	EventKey key(EventType::HOVER_ENTER, elementID);
	auto it = callbackMap.find(key);
	if (it != callbackMap.end())//if a vector of handlers exists for this ID
	{
		for (const LambdaHolder& lambdaHolder : it->second)
		{
			lambdaHolder.lambda(nullptr);//mouse position is not known here
		}
	}
}



void InputController::removeKeyPressLambda(uint32_t lambdaID, int keyCode) {
	EventKey key(EventType::KEY_PRESS, keyCode);
	const auto& it = callbackMap.find(key);
	if (it != callbackMap.end()) {
		vector<LambdaHolder>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				//remove elementLambdas vector from map if it is empty
				if (elementLambdas.empty()) {
					callbackMap.erase(it);
				}
				break; // Exit after removing the first matching lambda
			}
		}
	}
}