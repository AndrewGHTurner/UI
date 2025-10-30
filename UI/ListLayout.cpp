#include "pch.h"
#include "ListLayout.h"

void ListLayout::setVertical() {
	vertical = true;
	notifyRecalcNeeded();
}

void ListLayout::setHorizontal() {
	vertical = false;
	notifyRecalcNeeded();
}