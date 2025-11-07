#ifndef Page_H  
#define Page_H  

#include "Branch.h"  
#include <memory>  
#include "UI_DLL_Interface.h"
using namespace std;  

class UI_API Page {  
public:  
	unique_ptr<Branch> treeRoot; // the ui tree  
	virtual void createTree() = 0; // method to create the ui tree, must be implemented by derived classes  
	Page() {  
		treeRoot = nullptr;
	}  
private:  

};  

//extern "C" UI_API Page* createPage(Page);

using PagePtr = unique_ptr<Page>;


#endif // !Page_H
