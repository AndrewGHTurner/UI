#include "UI.h"

void UI::eventDispatcher(optional<Event>& event, RenderWindow &window) {
	if (event->getIf<Event::MouseButtonPressed>())
	{
		leftDownAt(Mouse::getPosition(window));
	}
	else if (event->getIf<Event::MouseButtonReleased>())
	{
		leftUpAt(Mouse::getPosition(window));
	}
}