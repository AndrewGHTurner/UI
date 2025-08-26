#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include "CallBack.h"
#include <cstdint>
#include "UI_DLL_Interface.h"
#include <functional>
using namespace std;

class UI_API BehviourManager {
protected:
	static uint32_t nextID;
	unordered_map<int, vector<unique_ptr<CallBack>>> leftDownCallbacks;//callbacks for when the left mouse button is pressed down
	unordered_map<int, vector<unique_ptr<CallBack>>> leftUpCallbacks;
	unordered_map<int, vector<unique_ptr<CallBack>>> mouseWheelScrollCallbacks;//callbacks for when the mouse wheel is scrolled

	unordered_map<int, vector<function<void()>>> leftDownLambdas;//SHOULD PROBS TURN THIS INTO A VECTOR OF LAMBDAS TO ALLOW MULTIPLE LAMBDAS TO BE ADDED
public:
	// Delete copy operations because unique_ptrs cannot be copied
	BehviourManager(const BehviourManager&) = delete;
	BehviourManager& operator=(const BehviourManager&) = delete;

	// Allow move operations
	BehviourManager(BehviourManager&&) noexcept = default;
	BehviourManager& operator=(BehviourManager&&) noexcept = default;

	BehviourManager() = default;
	static uint32_t newID();

	void addLeftDown(unique_ptr<CallBack> newCallback, int boxID);
	void addLeftDown(function<void()> lambda, int boxID);

	void addLeftUpCallback(unique_ptr<CallBack> newCallback, int boxID);
	void addMouseWheelCallback(unique_ptr<CallBack> newCallback, int boxID);
	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif