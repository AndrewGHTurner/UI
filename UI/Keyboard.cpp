#include "pch.h"
#include "EventType.h"

void UI::handleKeyPress(uint32_t keyCode)
{
	EventKey key(EventType::KEY_PRESS, keyCode);
	const auto it = currentPage->registry.callbackMap.find(key);
	EventData data;
	if (it != currentPage->registry.callbackMap.end())
	{
		for (const EventCallback& lambdaHolder : it->second)
		{
			lambdaHolder.lambda(data);
		}
	}
}