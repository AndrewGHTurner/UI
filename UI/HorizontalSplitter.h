#ifndef HORIZONTAL_SPLITTER
#define HORIZONTAL_SPLITTER


#include "UI_DLL_Interface.h"
#include "Branch.h"
#include "Proportioned.h"
#include "SplitterHandle.h"

namespace internal {
	class UI_API HorizontalSplitter : public Branch, private Proportioned {
	public:
		HorizontalSplitter(Vector2f origin, Vector2f siz);
		HorizontalSplitter();

		/**@note should make an add multiple function so that the proportions vector isn't needlesly recalculated. Or have a flag
		*/
		void add(unique_ptr<TreeNode> child, int proportion);
		void add(Facade& child, int proportion);
		void calcPositions() override;
	private:
		using Branch::add;
	};
}

using HorizontalSplitterPtr = unique_ptr<internal::HorizontalSplitter>;

UI_API HorizontalSplitterPtr HorizontalSplitter();

UI_API HorizontalSplitterPtr HorizontalSplitter(Vector2f origin, Vector2f siz);

#endif