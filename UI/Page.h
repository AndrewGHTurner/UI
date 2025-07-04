#ifndef Page_H  
#define Page_H  

#include "Branch.h"  
#include "UI.h"  
#include <memory>  
using namespace std;  

class Page {  
public:  
static UI* ui; // Declaration only  
unique_ptr<Branch> treeRoot; // the ui tree  
virtual void createTree() = 0; // method to create the ui tree, must be implemented by derived classes  
Page() {  
	treeRoot = nullptr;
}  
private:  

};  


#endif // !Page_H
