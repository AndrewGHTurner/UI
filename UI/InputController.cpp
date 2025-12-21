#include "pch.h"
#include "InputController.h"
#include <SFML/System/Vector2.hpp>
#include "CallbackLambdaHolders.h"
#include "EventType.h"
using namespace sf;

uint32_t InputController::nextID = 0;

uint32_t InputController::newID() {
	return nextID += 1;
}

uint32_t InputController::insertCallback(EventType type, const function<void(EventData)>& lambda, int boxID)
{
	EventKey key(type, boxID);
	uint32_t lambdaID = UI::getInstance()->newID();
	auto& callbackVector = this->currentPage->registry.callbackMap[key]; // creates empty vector if needed
	callbackVector.emplace_back(EventCallback(lambdaID, lambda));
	return lambdaID;
}

uint32_t InputController::addLeftDown(function<void(EventData)> lambda, int boxID)
{
	return insertCallback(EventType::LEFT_CLICK_DOWN, lambda, boxID);
}

uint32_t InputController::addLeftUp(function<void(EventData)> lambda, int boxID, bool allowSlideOff)
{
	uint32_t lambdaID = insertCallback(EventType::LEFT_CLICK_UP, lambda, boxID);
	//record if this lambda is conditional
	if (allowSlideOff)
	{
		this->currentPage->registry.conditionalReleaseLambdaIDs.insert(lambdaID);
	}
	return lambdaID;
}

uint32_t InputController::addLeftUp(function<void(EventData)> lambda)
{
	return insertCallback(EventType::LEFT_CLICK_UP, lambda, globalEventBoxID);
}

uint32_t InputController::addMouseWheelLambda(function<void(EventData)> lambda, int boxID)
{
	return insertCallback(EventType::MOUSE_WHEEL, lambda, boxID);
}

uint32_t InputController::addMouseMovementLambda(function<void(EventData)> lambda)
{
	return insertCallback(EventType::HOVER_MOVE, lambda, globalEventBoxID);
}

uint32_t InputController::addHoverEnterLambda(function<void(EventData)> lambda, int boxID)
{
	return insertCallback(EventType::HOVER_ENTER, lambda, boxID);
}

uint32_t InputController::addHoverExitLambda(function<void(EventData)> lambda, int boxID)
{
	return insertCallback(EventType::HOVER_EXIT, lambda, boxID);
}

uint32_t InputController::addKeyPressLambda(function<void(EventData)> lambda, int keyCode)
{
	return insertCallback(EventType::KEY_PRESS, lambda, keyCode);
}



void InputController::removeHoverExitLambda(uint32_t boxID, uint32_t lambdaID) {
	EventKey key(EventType::HOVER_EXIT, boxID);
	const auto& it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end()) {
		vector<EventCallback>& elementLambdas = it->second;
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
	const auto& it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end()) {
		vector<EventCallback>& elementLambdas = it->second;
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
	const auto& it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end()) {
		vector<EventCallback>& elementLambdas = it->second;
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
	const auto& it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end()) {
		vector<EventCallback>& elementLambdas = it->second;
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
		this->currentPage->registry.callbackMap.erase(key);
	}
}

void InputController::executeHoverEnterLambdas(int elementID)
{
	EventKey key(EventType::HOVER_ENTER, elementID);
	auto it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end())//if a vector of handlers exists for this ID
	{
		for (const EventCallback& lambdaHolder : it->second)
		{
			EventData data;
			lambdaHolder.lambda(data);//mouse position is not known here
		}
	}
}



void InputController::removeKeyPressLambda(uint32_t lambdaID, int keyCode) {
	EventKey key(EventType::KEY_PRESS, keyCode);
	const auto& it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end()) {
		vector<EventCallback>& elementLambdas = it->second;
		for (auto it2 = elementLambdas.begin(); it2 != elementLambdas.end(); ++it2)
		{
			if (it2->lambdaID == lambdaID) {
				elementLambdas.erase(it2);
				//remove elementLambdas vector from map if it is empty
				if (elementLambdas.empty()) {
					this->currentPage->registry.callbackMap.erase(it);
				}
				break; // Exit after removing the first matching lambda
			}
		}
	}
}


void InputController::raiseEvent(EventType type, int boxID, Vector2i pos, int delta)
{
	EventKey key(type, boxID);
	const auto it = this->currentPage->registry.callbackMap.find(key);
	if (it != this->currentPage->registry.callbackMap.end())//if a vector of handlers exists for this ID
	{
		EventData eventData;
		eventData.mousePosition = pos;
		eventData.scrollDelta = delta;
		for (const EventCallback& lambdaHolder : it->second)
		{
			lambdaHolder.lambda(eventData);
		}
	}
}