#ifndef FACADE_H
#define FACADE_H

#include "TreeNode.h"
#include <memory>
#include "UI_DLL_Interface.h"

class UI_API Facade
{
protected:
	std::unique_ptr<TreeNode> rootNode;//this is the root ui node of the UI element managed by the facade
public:
	virtual std::unique_ptr<TreeNode> getRootNodeOwnership() = 0;
	virtual TreeNode* getRootNodePointer() = 0; //returns a pointer to the root node, not ownership
};

#endif