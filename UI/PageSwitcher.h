/*
class PageHolder that will hold pages and manages them (Page Class) 
*/
#ifndef PAGE_SWITCHER_H
#define PAGE_SWITCHER_H

#include "Page.h"
#include <vector>
#include "Branch.h"
#include "UI_DLL_Interface.h"

class UI_API PageSwitcher {
private:
	Branch* holder; //this is the ui branch that holds the page that is currently selected
public:
	PageSwitcher(const PageSwitcher&) = delete;             // disable copy constructor
	PageSwitcher& operator=(const PageSwitcher&) = delete;  // disable copy assignment
	PageSwitcher(PageSwitcher&&) noexcept = default;        // enable move constructor
	PageSwitcher& operator=(PageSwitcher&&) noexcept = default; // enable move assignment
	PageSwitcher(Branch& branch);

	int newPageID();

	int addPage(unique_ptr<Page> page);

	void setPage(int pageID, unique_ptr<Page> page);

	void showPage(int pageID);

		
private:
	vector<unique_ptr<Page>> pages;//vector to hold pages
	int currentTreeRootID = -1;//ID of the currently displayed page
	int currentPageID = -1;
};

#endif