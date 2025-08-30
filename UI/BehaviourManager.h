#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <unordered_map>
#include <cstdint>
#include "UI_DLL_Interface.h"
#include <functional>
#include <unordered_set>
#include <SFML/System/Vector2.hpp>

using namespace std;
using namespace sf;

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

struct MouseMovementLambdaHolder {
	uint32_t lambdaID;
	function<void(Vector2i)> lambda;
	MouseMovementLambdaHolder(uint32_t id, function<void(Vector2i)> func) : lambdaID(id), lambda(func) {}
};

class UI_API BehaviorManager {
private:
	
protected:
	static uint32_t nextID;
	//These unordered maps contain all lambda callbacks that are localised to particular elements
	unordered_map<int, vector<LambdaHolder>> leftDownLambdas;
	unordered_map<int, vector<LambdaHolder>> leftUpLambdas;
	unordered_map<int, vector<MouseWheelLambdaHolder>> mouseWheelLambdas;
	//These vectors contain all lambda callbacks that are not localised to particular elements
	vector<MouseMovementLambdaHolder> mouseMovementLambdas;//This will contain mouse movement lambdas to be called on every mouse movement and not locallised to a particular element
	vector<LambdaHolder> leftUpLambdasUnlocalized;

	unordered_set<uint32_t> conditionalReleaseLambdaIDs;//it is assumed that there will be fewer conditional than unconditional in complex UIs ... will need a right click equivalent at some point

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
	* 
	*/
	uint32_t addLeftDown(function<void()> lambda, int boxID);
	/**
	* @return The ID assigned to the lambda
	* @param conditional If true then the mouse must be within the box for the lambda to be executed on mouse release. Conditional for user actions such as changing page. conditional = false for graphical callbacks like changing button colour on release
	*/
	uint32_t addLeftUp(function<void()> lambda, int boxID, bool allowSlideOff = false);
	uint32_t addLeftUp(function<void()> lambda);
	/**
	* @return The ID assigned to the lambda
	*/
	uint32_t addMouseWheelLambda(function<void(int)> lambda, int boxID);

	uint32_t addMouseMovementLambda(function<void(Vector2i mousePosition)> lambda);

	void removeMouseMovementLambda(uint32_t lambdaID);

	void removeLeftUp(uint32_t lambdaID);

	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif