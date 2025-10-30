#ifndef LINEAR_LAYOUT_H
#define LINEAR_LAYOUT_H

#include "Branch.h"

class UI_API LinearLayout : public Branch {
private:
	bool vertical = true;
public:
	LinearLayout(Vector2f origin, Vector2f siz) : Branch(origin, size) {}
	LinearLayout() : Branch() {}
	bool isVertical() const noexcept { return vertical; }
	void setVertical();
	void setHorizontal();
};

#endif