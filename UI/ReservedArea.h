#ifndef RESERVED_AREA_H
#define RESERVED_AREA_H
#include "UI_DLL_Interface.h"
#include "TreeNode.h"
#include "InteractiveFluent.h"

class UI_API ReservedArea : public InteractiveFluent<ReservedArea, TreeNode> {
public:
	ReservedArea();

};

#endif