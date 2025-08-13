#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include "CallBack.h"
#include <cstdint>
#include "UI_DLL_Interface.h"
using namespace std;

class UI_API BehviourManager {
protected:
	static uint32_t nextID;
	unordered_map<int, vector<unique_ptr<Callback>>> leftDownCallbacks;//callbacks for when the left mouse button is pressed down
	unordered_map<int, vector<unique_ptr<Callback>>> leftUpCallbacks;
	unordered_map<int, vector<unique_ptr<Callback>>> mouseWheelScrollCallbacks;//callbacks for when the mouse wheel is scrolled
public:
	// Delete copy operations because unique_ptrs cannot be copied
	BehviourManager(const BehviourManager&) = delete;
	BehviourManager& operator=(const BehviourManager&) = delete;

	// Allow move operations
	BehviourManager(BehviourManager&&) noexcept = default;
	BehviourManager& operator=(BehviourManager&&) noexcept = default;

	BehviourManager() = default;
	static uint32_t newID();

	void addLeftDownCallback(unique_ptr<Callback> newCallback, int boxID);//returns unique id of new callback
	void addLeftUpCallback(unique_ptr<Callback> newCallback, int boxID);//returns unique id of new callback
	void addMouseWheelCallback(unique_ptr<Callback> newCallback, int boxID);//returns unique id of new callback
	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif