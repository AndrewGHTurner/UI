#include "PageSwitcher.h"


PageSwitcher::PageSwitcher(Branch& branch) {
	holder = &branch;
}

int PageSwitcher::newPageID() {
	unique_ptr<Page> nullPage = nullptr;
	int id = pages.size();
	pages.push_back(move(nullPage)); //add a null page to the vector
	return id;
}

int PageSwitcher::addPage(unique_ptr<Page> page) {
	int id = pages.size();
	pages.push_back(move(page));
	return id;
}

void PageSwitcher::setPage(int pageID, unique_ptr<Page> page) {
	if (pageID < 0 || pageID >= pages.size()) {
		throw std::out_of_range("Page ID is out of range");
	}
	unique_ptr<Page>& existingPage = pages[pageID];
	if (existingPage != nullptr) {
		throw std::runtime_error("Page with this ID already exists");
	}
	existingPage = move(page); //set the page at the specified ID
}

void PageSwitcher::showPage(int pageID)
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

