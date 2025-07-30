#include "BehaviourManager.h"

uint32_t BehviourManager::nextID = 0;

uint32_t BehviourManager::newID() {
	return nextID += 1;
}

void BehviourManager::addLeftDownCallback(unique_ptr<Callback> newCallback, int boxID)//returns unique id of new callback
{
	//check if a vector of callbacks already exists
	auto it = leftDownCallbacks.find(boxID);
	if (it != leftDownCallbacks.end())//if a vector of callbacks already exists
	{
		it->second.push_back(move(newCallback));//add the new callback to the existing vector
	}
	else//create the vector and add the callback
	{
		vector<unique_ptr<Callback>> vec;
		vec.push_back(move(newCallback));//pushing a copy ... will not go out of scope
		leftDownCallbacks[boxID] = move(vec);
	}
}

void BehviourManager::addLeftUpCallback(unique_ptr<Callback> newCallback, int boxID)
{
	//check if a vector of callbacks already exists
	auto it = leftUpCallbacks.find(boxID);
	if (it != leftUpCallbacks.end())//if a vector of callbacks already exists
	{
		it->second.push_back(move(newCallback));//add the new callback to the existing vector
	}
	else//create the vector and add the callback
	{
		vector<unique_ptr<Callback>> vec;
		vec.push_back(move(newCallback));//pushing a copy ... will not go out of scope
		leftUpCallbacks[boxID] = move(vec);
	}
}

void BehviourManager::addMouseWheelCallback(unique_ptr<Callback> newCallback, int boxID)
{
	//check if a vector of callbacks already exists
	auto it = mouseWheelScrollCallbacks.find(boxID);
	if (it != mouseWheelScrollCallbacks.end())//if a vector of callbacks already exists
	{
		it->second.push_back(move(newCallback));//add the new callback to the existing vector
	}
	else//create the vector and add the callback
	{
		vector<unique_ptr<Callback>> vec;
		vec.push_back(move(newCallback));//pushing a copy ... will not go out of scope
		mouseWheelScrollCallbacks[boxID] = move(vec);
	}
}