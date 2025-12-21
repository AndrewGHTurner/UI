#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "UI_DLL_Interface.h"
#include <unordered_map>
#include <cstdint>
#include <functional>
#include <unordered_set>
#include <SFML/System/Vector2.hpp>

enum class EventType : uint8_t;
class EventCallback;
class Page;
struct EventData;


/**
* @note the unordered maps may need to be replaced with a vector of vectors + a vector of free indexes ... this may be more scalable than an unordered map
*/
class UI_API InputController {
private:
	uint32_t insertCallback(EventType type, const function<void(EventData)>& lambda, int boxID);
protected:
	static uint32_t nextID;



public:
	Page* currentPage = nullptr;


	// Delete copy operations because unique_ptrs cannot be copied
	InputController(const InputController&) = delete;
	InputController& operator=(const InputController&) = delete;

	// Allow move operations
	InputController(InputController&&) noexcept = default;
	InputController& operator=(InputController&&) noexcept = default;

	InputController() = default;



	/**
	* @note If ID wrapping (after ~4 billion IDs ... never going to happen) becomes a problem, one solution is to  have multiple ID counters. eg one for element IDs and one for callback IDs
	*/
	static uint32_t newID();


	/**
* @return The ID assigned to the lambda
*
*/

	uint32_t addLeftDown(std::function<void(EventData)> lambda, int boxID);
	/**
	* @return The ID assigned to the lambda
	* @param conditional If true then the mouse must be within the box for the lambda to be executed on mouse release. Conditional for user actions such as changing page. conditional = false for graphical callbacks like changing button colour on release
	*/
	uint32_t addLeftUp(std::function<void(EventData)> lambda, int boxID, bool allowSlideOff = false);
	uint32_t addLeftUp(std::function<void(EventData)> lambda);
	/**
	* @return The ID assigned to the lambda
	*/
	//add lambdas
	uint32_t addMouseWheelLambda(std::function<void(EventData)> lambda, int boxID);
	uint32_t addMouseMovementLambda(std::function<void(EventData)> lambda);
	uint32_t addHoverEnterLambda(std::function<void(EventData)> lambda, int boxID);
	uint32_t addHoverExitLambda(std::function<void(EventData)> lambda, int boxID);
	uint32_t addKeyPressLambda(std::function<void(EventData)> lambda, int keyCode);
	//remove lambdas
	void removeKeyPressLambda(uint32_t lambdaID, int keyCode);
	void removeHoverExitLambda(uint32_t boxID, uint32_t lambdaID);
	void removeMouseMovementLambda(uint32_t lambdaID);
	void removeLeftUp(uint32_t lambdaID);
	void removeLeftDown(uint32_t lambdaID, uint32_t boxID);
	void removeAllLambdasForElement(int boxID);
	//execute lambdas
	void executeHoverEnterLambdas(int elementID);
	void raiseEvent(EventType type, int boxID, Vector2i pos = Vector2i(0, 0), int delta = 0);

	

	void clearID(int id) {
		//clickHandelers.erase(id);
	}
};

#endif