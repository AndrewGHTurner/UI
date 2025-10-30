#include "pch.h"
#include "LinearLayout.h"

void LinearLayout::setVertical() {
	vertical = true;
	notifyRecalcNeeded();
}

void LinearLayout::setHorizontal() {
	vertical = false;
	notifyRecalcNeeded();
}