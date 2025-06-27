#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include "CallBack.h"
#include <cstdint>
using namespace std;

class BehviourManager {
protected:
	static uint32_t nextID;
	unordered_map<int, vector<Callback>> clickHandelers;
public:
	static uint32_t newID();

	int addLeftDownCallback(Callback& newCallback, int boxID);//returns unique id of new callback
};

#endif