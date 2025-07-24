#include "UI.h"

void UI::eventDispatcher(optional<Event>& event, RenderWindow &window) {
	if (event->getIf<Event::MouseButtonPressed>())
	{
		leftDownAt(Mouse::getPosition(window));
	}
}