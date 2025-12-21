#ifndef CALLBACK_LAMBDA_HOLDERS_H
#define CALLBACK_LAMBDA_HOLDERS_H
#include <cstdint>
#include <functional>
#include <SFML/System/Vector2.hpp>

struct LambdaHolder {
	uint32_t lambdaID;
	std::function<void(void*)> lambda;
	LambdaHolder(uint32_t id, std::function<void()> func) : lambdaID(id) {
		lambda = [func](void* arg) {
			func();
		};
	}
	LambdaHolder(uint32_t id, std::function<void(int)> func) : lambdaID(id){
		lambda = [func](void* arg) {
			int intArg = *static_cast<int*>(arg);
			func(intArg);
			};
	}
	LambdaHolder(uint32_t id, std::function<void(sf::Vector2i)> func) : lambdaID(id) {
		lambda = [func](void* arg) {
			sf::Vector2i vecArg = *static_cast<sf::Vector2i*>(arg);
			func(vecArg);
			};
	}
};


#endif