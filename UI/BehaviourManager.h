#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include "CallBack.h"
#include <cstdint>
using namespace std;

class BehviourManager {
protected:
	static uint32_t nextID;
	unordered_map<int, vector<unique_ptr<Callback>>> leftDownCallbacks;//callbacks for when the left mouse button is pressed down
	unordered_map<int, vector<unique_ptr<Callback>>> leftUpCallbacks;
public:
	static uint32_t newID();

	void addLeftDownCallback(unique_ptr<Callback> newCallback, int boxID);//returns unique id of new callback
	void addLeftUpCallback(unique_ptr<Callback> newCallback, int boxID);//returns unique id of new callback
	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif