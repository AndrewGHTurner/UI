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
	else if (event->getIf <Event::MouseWheelScrolled>())
	{
		mouseWheelScrollAt(Mouse::getPosition(window), event->getIf<Event::MouseWheelScrolled>()->delta);
	}
	else if (event->getIf <Event::MouseMoved>())
	{
		mouseMovementAt(Mouse::getPosition(window));
	}
	else if (event->getIf <Event::Resized>())
	{
		Vector2u newSize = event->getIf<Event::Resized>()->size;
		screenTexture->resize(newSize);
		setSize(Vector2f(static_cast<float>(newSize.x), static_cast<float>(newSize.y)));
	}
}