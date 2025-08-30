#include "BehaviourManager.h"

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