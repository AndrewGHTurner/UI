#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include <cstdint>
#include "UI_DLL_Interface.h"
#include <functional>
#include <unordered_set>

using namespace std;

struct LambdaHolder {
	uint32_t lambdaID;
	function<void()> lambda;
	LambdaHolder(uint32_t id, function<void()> func) : lambdaID(id), lambda(func) {}
};

struct MouseWheelLambdaHolder {
	uint32_t lambdaID;
	function<void(int)> lambda;
	MouseWheelLambdaHolder(uint32_t id, function<void(int)> func) : lambdaID(id), lambda(func) {}
};

class UI_API BehaviorManager {
private:
	unordered_set<uint32_t> ;
protected:
	static uint32_t nextID;

	unordered_map<int, vector<LambdaHolder>> leftDownLambdas;//SHOULD PROBS TURN THIS INTO A VECTOR OF LAMBDAS TO ALLOW MULTIPLE LAMBDAS TO BE ADDED
	unordered_map<int, vector<LambdaHolder>> leftUpLambdas;
	
	unordered_map<int, vector<MouseWheelLambdaHolder>> mouseWheelLambdas;

public:
	// Delete copy operations because unique_ptrs cannot be copied
	BehaviorManager(const BehaviorManager&) = delete;
	BehaviorManager& operator=(const BehaviorManager&) = delete;

	// Allow move operations
	BehaviorManager(BehaviorManager&&) noexcept = default;
	BehaviorManager& operator=(BehaviorManager&&) noexcept = default;

	BehaviorManager() = default;

	/**
	* @note If ID wrapping (after ~4 billion IDs ... never going to happen) becomes a problem, one solution is to  have multiple ID counters. eg one for element IDs and one for callback IDs
	*/
	static uint32_t newID();

	/**
	* @return The ID assigned to the lambda
	*/
	uint32_t addLeftDown(function<void()> lambda, int boxID);
	/**
	* @return The ID assigned to the lambda
	*/
	uint32_t addLeftUp(function<void()> lambda, int boxID);
	/**
	* @return The ID assigned to the lambda
	*/
	uint32_t addMouseWheelLambda(function<void(int)> lambda, int boxID);
	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif