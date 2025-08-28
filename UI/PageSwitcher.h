/*
class PageHolder that will hold pages and manages them (Page Class) 
*/
#ifndef PAGE_SWITCHER_H
#define PAGE_SWITCHER_H

#include "Page.h"
#include <vector>
#include "Branch.h"
#include "UI_DLL_Interface.h"

/**
* @brief A class that holds multiple page objects. Pages are given IDs which are indexes into a vector of unique pointers to pages.
* @note a namedPageSwitcher class could be created that maps strings to page IDs
*/
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

	/**
	* @brief Add a page to the PageSwitcher.
	* @param pageID User decided id that will be used to access the page
	*/
	void addPage(unique_ptr<Page> page, int pageID);

	//void removeI

	void showPage(int pageID);

		
private:
	vector<unique_ptr<Page>> pages;//vector to hold pages
	unordered_map<int, int> idToIndexMap;//map to hold the mapping from page ID to index in the vector of pages
	int currentTreeRootID = -1;//ID of the currently displayed page
	int currentPageID = -1;
};

#endif