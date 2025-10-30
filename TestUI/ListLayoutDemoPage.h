#ifndef LIST_LAYOUT_DEMO_PAGE_H
#define LIST_LAYOUT_DEMO_PAGE_H

#include "Page.h"  
#include "PageSwitcher.h"

class ListLayoutDemoPage : public Page {

public:
	PageSwitcher& pageSwitcher;
	ListLayoutDemoPage(ListLayoutDemoPage&& other) = default; // Move constructor for HorizontalOrVertical
	ListLayoutDemoPage(PageSwitcher& pageSwitcher) : pageSwitcher(pageSwitcher) {
	}
	void createTree() override;
};


#endif // !LIST_LAYOUT_DEMO_PAGE_H
