#include "pch.h"
#include "EventType.h"

void UI::handleKeyPress(uint32_t keyCode)
{
	EventKey key(EventType::KEY_PRESS, keyCode);
	const auto it = currentPage->registry.callbackMap.find(key);
	if (it != currentPage->registry.callbackMap.end())
	{
		for (const LambdaHolder& lambdaHolder : it->second)
		{
			lambdaHolder.lambda(nullptr);
		}
	}
}