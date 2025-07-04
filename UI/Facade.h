#ifndef FACADE_H
#define FACADE_H

#include "TreeNode.h"
#include <memory>

class Facade
{
protected:
	TreeNode* rootNode;//this is the root ui node of the UI element managed by the facade
public:
	virtual TreeNode* getRootNode() = 0;
};

#endif