#include "pch.h"
#include "ListLayout.h"



void ListLayout::removeAllItems() {//NEED TO WORK ON CLEARING MEMORY AND UI LAMBDA CALLBACKS PROPERLY!!!
	children.clear();
	notifyRecalcNeeded();
}