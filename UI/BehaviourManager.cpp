#include "BehaviourManager.h"

uint32_t BehviourManager::nextID = 0;

uint32_t BehviourManager::newID() {
	return nextID += 1;
}

void BehviourManager::addLeftDown(unique_ptr<CallBack> newCallback, int boxID)//returns unique id of new callback
{
	//check if a vector of callbacks already exists
	auto it = leftDownCallbacks.find(boxID);
	if (it != leftDownCallbacks.end())//if a vector of callbacks already exists
	{
		it->second.push_back(move(newCallback));//add the new callback to the existing vector
	}
	else//create the vector and add the callback
	{
		vector<unique_ptr<CallBack>> vec;
		vec.push_back(move(newCallback));//pushing a copy ... will not go out of scope
		leftDownCallbacks[boxID] = move(vec);
	}
}

void BehviourManager::addLeftDown(function<void()> lambda, int boxID)
{
	auto it = leftDownLambdas.find(boxID);
	if (it != leftDownLambdas.end())//if a vector of callbacks already exists
	{
		it->second.push_back(lambda);//add the new callback to the existing vector
		return;
	}
	else {
		vector<function<void()>> vec;
		vec.push_back(lambda);//pushing a copy ... will not go out of scope
		leftDownLambdas[boxID] = move(vec);
		return;
	}
}

void BehviourManager::addLeftUpCallback(unique_ptr<CallBack> newCallback, int boxID)
{
	//check if a vector of callbacks already exists
	auto it = leftUpCallbacks.find(boxID);
	if (it != leftUpCallbacks.end())//if a vector of callbacks already exists
	{
		it->second.push_back(move(newCallback));//add the new callback to the existing vector
	}
	else//create the vector and add the callback
	{
		vector<unique_ptr<CallBack>> vec;
		vec.push_back(move(newCallback));//pushing a copy ... will not go out of scope
		leftUpCallbacks[boxID] = move(vec);
	}
}

void BehviourManager::addMouseWheelLambda(function<void(int)> lambda, int boxID)
{
	auto it = mouseWheelLambdas.find(boxID);
	if (it != mouseWheelLambdas.end())//if a vector of callbacks already exists
	{
		it->second.push_back(lambda);//add the new callback to the existing vector
		return;
	}
	else {
		vector<function<void(int)>> vec;
		vec.push_back(lambda);//pushing a copy ... will not go out of scope
		mouseWheelLambdas[boxID] = move(vec);
		return;
	}
}