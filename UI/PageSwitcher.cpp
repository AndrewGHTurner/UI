#include "pch.h"
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

void PageSwitcher::addPage(unique_ptr<Page> page, int pageID) {
	pages.push_back(move(page));
	idToIndexMap[pageID] = pages.size() - 1;
}

void PageSwitcher::showPage(int pageID)
{
	//retrieve old ui tree from the holder branch and return its ownership to the page
	unique_ptr<TreeNode> treeRoot = holder->retrieve(currentTreeRootID);

	unique_ptr<Branch> previousTree = unique_ptr<Branch>(static_cast<Branch*>(treeRoot.release()));
	//move ownership of the previous tree, if it exists, back to its page
	if (previousTree != nullptr && currentPageID != -1) {
		pages[idToIndexMap[currentPageID]]->treeRoot = move(previousTree);
		pages[idToIndexMap[currentPageID]]->onHide();
	}
	currentPageID = pageID;
	//add the next page to the holder branch
	unique_ptr<Page>& page = pages[idToIndexMap[pageID]];
	//check that the page has built its ui tree
	if (page->treeRoot == nullptr) {
		page->createTree(); //create the ui tree if it has not been created yet
	}
	page->onShow();
	currentTreeRootID = page->treeRoot.get()->id;
	holder->add(move(page->treeRoot));
}

Page& PageSwitcher::getPage(int pageID)
{
	return *pages[idToIndexMap[pageID]];
}
