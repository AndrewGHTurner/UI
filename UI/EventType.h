#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H
#include <cstdint>
#include <cstddef>
#include <functional>

//std::unordered_map<uint32_t, std::vector<LambdaHolder>> leftDownLambdas;
//std::unordered_map<uint32_t, std::vector<LambdaHolder>> leftUpLambdas;
//std::unordered_map<uint32_t, std::vector<MouseWheelLambdaHolder>> mouseWheelLambdas;
//std::unordered_map<uint32_t, std::vector<MouseMovementLambdaHolder>> hoverEnterLambdas;
//std::unordered_map<uint32_t, std::vector<MouseMovementLambdaHolder>> hoverExitLambdas;
//std::unordered_map<uint32_t, std::vector<LambdaHolder>> hoverLambdas;//holds lambdas for when the mouse moves within an element
//std::unordered_map<uint32_t, std::vector<LambdaHolder>> keyPressLambdas;//holds lambdas for
enum class EventType : uint8_t {
	LEFT_CLICK_DOWN,
	LEFT_CLICK_UP,
	MOUSE_WHEEL,
	HOVER_ENTER,
	HOVER_EXIT,
	HOVER_MOVE,
	KEY_PRESS
};

struct EventKey {
    EventType type;
    uint32_t elementID;

    bool operator==(const EventKey& other) const {
        return type == other.type && elementID == other.elementID;
    }
	EventKey(EventType t, uint32_t id) : type(t), elementID(id) {}
};

struct EventKeyHash {
    std::size_t operator()(const EventKey& key) const noexcept {
        return std::hash<uint32_t>()(static_cast<uint32_t>(key.type))
            ^ (std::hash<uint32_t>()(key.elementID) << 1);
    }
};

#endif