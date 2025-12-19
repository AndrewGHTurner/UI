
#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CallbackLambdaHolders.h"
#include <memory>

enum class EventTypes;
struct EventKey;
struct EventKeyHash;

const int globalEventBoxID = -1;//used to indicate that an event is not localised to a particular element
/**
* @brief Input controller acts as a registry for callbacks of elements.
*/
class InputController {
private:
	std::unordered_map<EventKey, std::vector<LambdaHolder>, EventKeyHash> callbackMap;
	//These std::vectors contain all lambda callbacks that are not localised to particular elements
	std::unordered_set<uint32_t> hoveredElementIDs;//holds each frames hoveded elements
	std::unordered_set<uint32_t> conditionalReleaseLambdaIDs;//it is assumed that there will be fewer conditional than unconditional in complex UIs ... will need a right click equivalent at some point
	
	uint32_t insertCallback(EventType type, const function<void()>& lambda, int boxID);
	uint32_t insertCallback(EventType type, const function<void(int)>& lambda, int boxID);
	uint32_t insertCallback(EventType type, const function<void(Vector2i)>& lambda, int boxID);
public:
	/**
* @return The ID assigned to the lambda
*
*/

	uint32_t addLeftDown(std::function<void()> lambda, int boxID);
	/**
	* @return The ID assigned to the lambda
	* @param conditional If true then the mouse must be within the box for the lambda to be executed on mouse release. Conditional for user actions such as changing page. conditional = false for graphical callbacks like changing button colour on release
	*/
	uint32_t addLeftUp(std::function<void()> lambda, int boxID, bool allowSlideOff = false);
	uint32_t addLeftUp(std::function<void()> lambda);
	/**
	* @return The ID assigned to the lambda
	*/
	//add lambdas
	uint32_t addMouseWheelLambda(std::function<void(int)> lambda, int boxID);
	uint32_t addMouseMovementLambda(std::function<void(sf::Vector2i mousePosition)> lambda);
	uint32_t addHoverEnterLambda(std::function<void(sf::Vector2i mousePosition)> lambda, int boxID);
	uint32_t addHoverExitLambda(std::function<void(sf::Vector2i mousePosition)> lambda, int boxID);
	uint32_t addKeyPressLambda(std::function<void()> lambda, int keyCode);
	//remove lambdas
	void removeKeyPressLambda(uint32_t lambdaID, int keyCode);
	void removeHoverExitLambda(uint32_t boxID, uint32_t lambdaID);
	void removeMouseMovementLambda(uint32_t lambdaID);
	void removeLeftUp(uint32_t lambdaID);
	void removeLeftDown(uint32_t lambdaID, uint32_t boxID);
	void removeAllLambdasForElement(int boxID);
	//execute lambdas
	void executeHoverEnterLambdas(int elementID);
};



#endif