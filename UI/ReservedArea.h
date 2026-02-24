#ifndef RESERVED_AREA_H
#define RESERVED_AREA_H
#include "UI_DLL_Interface.h"
#include "TreeNode.h"
#include "InteractiveFluent.h"
namespace internal {
	class UI_API ReservedArea : public InteractiveFluent<ReservedArea, TreeNode> {
	public:
		ReservedArea();

	};
}

using ReservedAreaPtr = std::unique_ptr<class internal::ReservedArea>;

ReservedAreaPtr UI_API ReservedArea();

#endif