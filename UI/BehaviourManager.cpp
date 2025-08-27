#include "BehaviourManager.h"

uint32_t BehviourManager::nextID = 0;

uint32_t BehviourManager::newID() {
	return nextID += 1;
}

void BehviourManager::addLeftDown(function<void()> lambda, int boxID)
{
	auto it = leftDownLambdas.find(boxID);
	if (it != leftDownLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(lambda);//add the new lambda to the existing vector
		return;
	}
	else {
		vector<function<void()>> vec;
		vec.push_back(lambda);//pushing a copy ... will not go out of scope
		leftDownLambdas[boxID] = move(vec);
		return;
	}
}

void BehviourManager::addLeftUp(function<void()> lambda, int boxID)
{
	auto it = leftUpLambdas.find(boxID);
	if (it != leftUpLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(lambda);//add the new lambda to the existing vector
		return;
	}
	else {
		vector<function<void()>> vec;
		vec.push_back(lambda);//pushing a copy ... will not go out of scope
		leftUpLambdas[boxID] = move(vec);
		return;
	}
}

void BehviourManager::addMouseWheelLambda(function<void(int)> lambda, int boxID)
{
	auto it = mouseWheelLambdas.find(boxID);
	if (it != mouseWheelLambdas.end())//if a vector of lambdas already exists
	{
		it->second.push_back(lambda);//add the new lambda to the existing vector
		return;
	}
	else {
		vector<function<void(int)>> vec;
		vec.push_back(lambda);//pushing a copy ... will not go out of scope
		mouseWheelLambdas[boxID] = move(vec);
		return;
	}
}