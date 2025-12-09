#ifndef LINEAR_LIST_FLUENT_H
#define LINEAR_LIST_FLUENT_H

#include "UI.h"
#include "Branch.h"

template<typename Derived>

class LinearListFluent : public Branch {
private:
	bool vertical = true;
protected:
	int elementMargin = 0;
public:
	LinearListFluent(Vector2f origin, Vector2f siz) : Branch(origin, siz) {}
	LinearListFluent() : Branch() {}
	bool isVertical() const noexcept { return vertical; }
	Derived& setMargin(int margin)
	{
		elementMargin = margin;
		notifyRecalcNeeded();
		return static_cast<Derived&>(*this);
	}
	Derived& setVertical()
	{
		vertical = true;
		notifyRecalcNeeded();
		return static_cast<Derived&>(*this);
	}
	Derived& setHorizontal()
	{
		vertical = false;
		notifyRecalcNeeded();
		return static_cast<Derived&>(*this);
	}

	Derived& removeAllItems() {//NEED TO WORK ON CLEARING MEMORY AND UI LAMBDA CALLBACKS PROPERLY!!!
		children.clear();
		notifyRecalcNeeded();
		return static_cast<Derived&>(*this);
	}
};

#endif