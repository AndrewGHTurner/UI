#ifndef Page_H  
#define Page_H  

#include "UI_DLL_Interface.h"
#include "Branch.h"  
#include <memory>  
#include "InputController.h"
#include "CallbackRegistry.h" 

class UI_API Page {  
public:  
	unique_ptr<Branch> treeRoot; // the ui tree  
	virtual void createTree() = 0; // method to create the ui tree, must be implemented by derived classes  
	virtual void onShow() {}; // method called when the page is shown
	virtual void onHide() {}; // method called when the page is hidden
	CallbackRegistry registry;
	Page() {  
		treeRoot = nullptr;
	}  
private:  

};  

//extern "C" UI_API Page* createPage(Page);

using PagePtr = unique_ptr<Page>;


#endif // !Page_H
