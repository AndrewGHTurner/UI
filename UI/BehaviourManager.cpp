#include "BehaviourManager.h"

uint32_t BehviourManager::nextID = 0;

uint32_t BehviourManager::newID() {
	return nextID += 1;
}

int BehviourManager::addLeftDownCallback(Callback& newCallback, int boxID)//returns unique id of new callback
{
	//	Callback newCallback(onClickFunk, param, newID());
		//check if a vector of callbacks already exists
	auto it = clickHandelers.find(boxID);
	if (it != clickHandelers.end())//if a vector of callbacks already exists
	{
		it->second.push_back(newCallback);
	}
	else//create the vector and add the callback
	{
		vector<Callback> vec;
		vec.push_back(newCallback);//pushing a copy ... will not go out of scope
		clickHandelers[boxID] = vec;
	}
	return newCallback.id;
}