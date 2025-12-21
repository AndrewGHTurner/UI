
#ifndef CALLBACK_REGISTRY_H
#define CALLBACK_REGISTRY_H
#include "UI_DLL_Interface.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CallbackLambdaHolders.h"
#include <memory>
#include "EventType.h"

const int globalEventBoxID = -1;//used to indicate that an event is not localised to a particular element
/**
* @brief Input controller acts as a registry for callbacks of elements.
*/
class UI_API CallbackRegistry {
public:
	std::unordered_map<EventKey, std::vector<LambdaHolder>, EventKeyHash> callbackMap;
	//These std::vectors contain all lambda callbacks that are not localised to particular elements
	std::unordered_set<uint32_t> hoveredElementIDs;//holds each frames hoveded elements
	std::unordered_set<uint32_t> conditionalReleaseLambdaIDs;//it is assumed that there will be fewer conditional than unconditional in complex UIs ... will need a right click equivalent at some point
};



#endif