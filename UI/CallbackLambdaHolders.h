#ifndef CALLBACK_LAMBDA_HOLDERS_H
#define CALLBACK_LAMBDA_HOLDERS_H
#include <cstdint>
#include <functional>
#include <SFML/System/Vector2.hpp>

struct EventData {
	int scrollDelta;
	sf::Vector2i mousePosition;
};

struct EventCallback {
	uint32_t lambdaID;
	std::function<void(const EventData& data)> lambda;
	EventCallback(uint32_t id, std::function<void(const EventData& data)> func) : lambdaID(id), lambda(func) {}
};


#endif