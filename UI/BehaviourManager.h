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

class LambdaHolder;


/**
* @note the unordered maps may need to be replaced with a vector of vectors + a vector of free indexes ... this may be more scalable than an unordered map
*/
class UI_API BehaviorManager {
private:
	Page* currentPage = nullptr;
protected:
	static uint32_t nextID;


public:
	//unordered_map<uint32_t, vector<LambdaHolder>>& getLeftDownLambdas() {
	//	return leftDownLambdas;
	//}
	//unordered_map<uint32_t, vector<LambdaHolder>>& getHoverLambdas() {
	//	return hoverLambdas;
	//}
	//unordered_map<uint32_t, vector<MouseMovementLambdaHolder>>& getHoverEnterLambdas() {
	//	return hoverEnterLambdas;
	//}


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





	

	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif