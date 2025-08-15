#include <SFML/System/Vector2.hpp>
using namespace sf;

#ifndef BOX_H
#define BOX_H
#include "UI_DLL_Interface.h"
//2d box on the screen
/**
@brief represents an area on the screen
@note antiorigin could be removed an calculated when needed instead. This would be slower but would remove 8 bytes from every TreeNode
*/
class UI_API Box {
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