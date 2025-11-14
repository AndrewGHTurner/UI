#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "UI_DLL_Interface.h"
#include "ListLayout.h"
#include <memory>

namespace internal {
	class UI_API StaticList : public ListLayout {
	public:
		StaticList();
		void calcPositions() override;
	};
}

using StaticListPtr = std::unique_ptr<internal::StaticList>;

StaticListPtr UI_API StaticList();

#endif