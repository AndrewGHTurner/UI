/*
class PageHolder that will hold pages and manages them (Page Class) 
*/
#ifndef PAGE_HOLDER_H
#define PAGE_HOLDER_H

#include "Page.h"
#include <vector>

class PageHolder {
public:
	PageHolder() {
		
	}

	int addPage(unique_ptr<Page> page) {
		int id = pages.size();
		pages.push_back(move(page));
		return id;
	}
private:
	vector<unique_ptr<Page>> pages; // vector to hold pages
};

#endif