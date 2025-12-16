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

/**
* @note the unordered maps may need to be replaced with a vector of vectors + a vector of free indexes ... this may be more scalable than an unordered map
*/
class UI_API BehaviorManager {
private:
	
protected:
	static uint32_t nextID;
	//These unordered maps contain all lambda callbacks that are localised to particular elements
	unordered_map<uint32_t, vector<LambdaHolder>> leftDownLambdas;
	unordered_map<uint32_t, vector<LambdaHolder>> leftUpLambdas;
	unordered_map<uint32_t, vector<MouseWheelLambdaHolder>> mouseWheelLambdas;
	unordered_map<uint32_t, vector<MouseMovementLambdaHolder>> hoverEnterLambdas;
	unordered_map<uint32_t, vector<MouseMovementLambdaHolder>> hoverExitLambdas;
	unordered_map<uint32_t, vector<LambdaHolder>> hoverLambdas;//holds lambdas for when the mouse moves within an element
	unordered_map<uint32_t, vector<LambdaHolder>> keyPressLambdas;//holds lambdas for when the mouse moves out of an element
	//These vectors contain all lambda callbacks that are not localised to particular elements
	vector<MouseMovementLambdaHolder> mouseMovementLambdas;//This will contain mouse movement lambdas to be called on every mouse movement and not locallised to a particular element
	vector<LambdaHolder> leftUpLambdasUnlocalized;

	unordered_set<uint32_t> hoveredElementIDs;//holds each frames hoveded elements
	
	

	unordered_set<uint32_t> conditionalReleaseLambdaIDs;//it is assumed that there will be fewer conditional than unconditional in complex UIs ... will need a right click equivalent at some point

public:
	unordered_map<uint32_t, vector<LambdaHolder>>& getLeftDownLambdas() {
		return leftDownLambdas;
	}
	unordered_map<uint32_t, vector<LambdaHolder>>& getHoverLambdas() {
		return hoverLambdas;
	}
	unordered_map<uint32_t, vector<MouseMovementLambdaHolder>>& getHoverEnterLambdas() {
		return hoverEnterLambdas;
	}


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

	uint32_t addHoverEnterLambda(function<void(Vector2i mousePosition)> lambda, int boxID);

	uint32_t addHoverExitLambda(function<void(Vector2i mousePosition)> lambda, int boxID);

	uint32_t addKeyPressLambda(function<void()> lambda, int keyCode);

	void removeKeyPressLambda(uint32_t lambdaID, int keyCode);

	void removeHoverExitLambda(uint32_t boxID, uint32_t lambdaID);

	void removeMouseMovementLambda(uint32_t lambdaID);

	void removeLeftUp(uint32_t lambdaID);

	void removeLeftDown(uint32_t lambdaID, uint32_t boxID);

	void removeAllLambdasForElement(int boxID);

	void executeHoverEnterLambdas(int elementID);

	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif