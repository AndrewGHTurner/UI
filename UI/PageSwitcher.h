/*
class PageHolder that will hold pages and manages them (Page Class) 
*/
#ifndef PAGE_SWITCHER_H
#define PAGE_SWITCHER_H

#include "Page.h"
#include <vector>
#include "Branch.h"

class PageSwitcher{
private:
	Branch* holder; //this is the ui branch that holds the page that is currently selected
public:
	PageSwitcher(Branch& branch) {
		holder = &branch;
	}

	int addPage(unique_ptr<Page> page) {
		int id = pages.size();
		pages.push_back(move(page));
		return id;
	}

    void showPage(int pageID)
    {
		//retrieve old ui tree from the holder branch and return its ownership to the page
		unique_ptr<TreeNode> treeRoot = holder->retrieve(currentTreeRootID);
		
		unique_ptr<Branch> previousTree = unique_ptr<Branch>(static_cast<Branch*>(treeRoot.release()));
		//move ownership of the previous tree, if it exists, back to its page
		if (previousTree != nullptr && currentPageID != -1) {
			pages[currentPageID]->treeRoot = move(previousTree);
		}
		currentPageID = pageID;
		//add the next page to the holder branch
		unique_ptr<Page>& page = pages[pageID];
		//check that the page has built its ui tree
		if (page->treeRoot == nullptr) {
			page->createTree(); //create the ui tree if it has not been created yet
		}
		currentTreeRootID = page->treeRoot.get()->id;
		holder->add(move(page->treeRoot));
    }

		
private:
	vector<unique_ptr<Page>> pages;//vector to hold pages
	int currentTreeRootID = -1;//ID of the currently displayed page
	int currentPageID = -1;
};

#endif