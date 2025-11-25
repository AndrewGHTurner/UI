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

void ListLayout::removeAllItems() {//NEED TO WORK ON CLEARING MEMORY AND UI LAMBDA CALLBACKS PROPERLY!!!
	children.clear();
	notifyRecalcNeeded();
}