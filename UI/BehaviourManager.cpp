#include "BehaviourManager.h"
#include <SFML/System/Vector2.hpp>
using namespace sf;

uint32_t BehaviorManager::nextID = 0;

uint32_t BehaviorManager::newID() {
	return nextID += 1;
}

uint32_t BehaviorManager::addLeftDown(function<void()> lambda, int boxID)
{
	uint32_t lambdaID = newID();
	auto it = leftDownLambdas.find(boxID);
	if (it != leftDownLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(LambdaHolder(lambdaID, lambda));//add the new lambda to the existing vector
	}
	else {
		vector<LambdaHolder> vec;
		vec.push_back(LambdaHolder(lambdaID, lambda));//pushing a copy ... will not go out of scope
		leftDownLambdas[boxID] = move(vec);
	}
	return lambdaID;
}

uint32_t BehaviorManager::addLeftUp(function<void()> lambda, int boxID, bool allowSlideOff)
{
	uint32_t lambdaID = newID();
	auto it = leftUpLambdas.find(boxID);
	if (it != leftUpLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(LambdaHolder(lambdaID, lambda));//add the new lambda to the existing vector
	}
	else {
		vector<LambdaHolder> vec;
		vec.push_back(LambdaHolder(lambdaID, lambda));//pushing a copy ... will not go out of scope
		leftUpLambdas[boxID] = move(vec);
	}
	//record if this lambda is conditional
	if (allowSlideOff)
	{
		conditionalReleaseLambdaIDs.insert(lambdaID);
	}
	return lambdaID;
}

uint32_t BehaviorManager::addLeftUp(function<void()> lambda)
{
	uint32_t lambdaID = newID();
	LambdaHolder holder(lambdaID, lambda);
	leftUpLambdasUnlocalized.push_back(holder);
	return lambdaID;
}

uint32_t BehaviorManager::addMouseWheelLambda(function<void(int)> lambda, int boxID)
{
	uint32_t lambdaID = newID();
	auto it = mouseWheelLambdas.find(boxID);
	if (it != mouseWheelLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(MouseWheelLambdaHolder(lambdaID, lambda));//add the new lambda to the existing vector
	}
	else {
		vector<MouseWheelLambdaHolder> vec;
		vec.push_back(MouseWheelLambdaHolder(lambdaID, lambda));//pushing a copy ... will not go out of scope
		mouseWheelLambdas[boxID] = move(vec);
	}
	return lambdaID;
}

uint32_t BehaviorManager::addMouseMovementLambda(function<void(Vector2i)> lambda)
{
	uint32_t id = newID();
	mouseMovementLambdas.push_back(MouseMovementLambdaHolder(id, lambda));
	return id;
}

void BehaviorManager::removeMouseMovementLambda(uint32_t lambdaID) {
	for (auto it = mouseMovementLambdas.begin(); it != mouseMovementLambdas.end(); it++) {
		if (it->lambdaID == lambdaID) {
			mouseMovementLambdas.erase(it);
			break; // Exit after removing the first matching lambda
		}
	}
}

void BehaviorManager::removeLeftUp(uint32_t lambdaID) {
	for (auto it = leftUpLambdasUnlocalized.begin(); it != leftUpLambdasUnlocalized.end(); it++) {
		if (it->lambdaID == lambdaID) {
			leftUpLambdasUnlocalized.erase(it);
			break; // Exit after removing the first matching lambda
		}
	}
}