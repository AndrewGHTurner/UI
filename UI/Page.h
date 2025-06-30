/*
class to hold a ui tree and the method needed to create it. could have a retainied method etc
*/
#ifndef Page_H
#define Page_H

#include "TreeNode.h"
#include <memory>
using namespace std;

class Page {
public:
	unique_ptr<TreeNode> tree; // the ui tree
	virtual void createTree() = 0; // method to create the tree, must be implemented by derived classes
	Page() {

	}
};
#endif // !Page_H
