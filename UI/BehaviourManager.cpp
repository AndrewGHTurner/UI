#include "pch.h"
#include "BehaviourManager.h"
#include <SFML/System/Vector2.hpp>
#include "CallbackLambdaHolders.h"
using namespace sf;

uint32_t BehaviorManager::nextID = 0;

uint32_t BehaviorManager::newID() {
	return nextID += 1;
}



