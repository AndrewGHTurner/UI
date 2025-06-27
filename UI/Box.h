#include <SFML/System/Vector2.hpp>
using namespace sf;

#ifndef BOX_H
#define BOX_H

//2d box on the screen
class Box {
protected:
	Vector2f origin;//top right
	Vector2f antiOrigin;//bottom left
	Vector2f size;
public:
	Vector2f getOrigin() {
		return origin;
	}
	Vector2f getSize() {
		return size;
	}

};

#endif