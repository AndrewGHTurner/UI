#ifndef LINEAR_LAYOUT_H
#define LINEAR_LAYOUT_H

#include "Branch.h"
#include "LinearListFluent.h"

class UI_API ListLayout : public LinearListFluent<ListLayout> {
public:
	ListLayout(Vector2f origin, Vector2f siz) : LinearListFluent(origin, size) {}
	ListLayout() : LinearListFluent() {}
	void removeAllItems();
};

#endif