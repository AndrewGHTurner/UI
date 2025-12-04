#ifndef HORIZONTAL_PROPORTIONAL_SPACED_BAR
#define HORIZONTAL_PROPORTIONAL_SPACED_BAR

#include <memory>
#include "Facade.h"
#include "UI_DLL_Interface.h"
#include "Branch.h"
#include "LinearListFluent.h"

namespace internal {
	class UI_API ProportionalSpacedList : public LinearListFluent<ProportionalSpacedList> {
	private:
		vector<int> proportions;
		int totalProportion = 0;
	public:
		ProportionalSpacedList();
		ProportionalSpacedList(Vector2f origin, Vector2f siz);
		using LinearListFluent::add;
		//proportion is the amount of space the widget needs... will be relative to the proportions given to other widgets
		void add(Facade& facade, int proportion);
		void add(unique_ptr<TreeNode> child, int proportion);

		void calcPositions() override;
	};
}

using ProportionalSpacedListPtr = unique_ptr<internal::ProportionalSpacedList>;
UI_API ProportionalSpacedListPtr ProportionalSpacedList();
UI_API ProportionalSpacedListPtr ProportionalSpacedList(Vector2f origin, Vector2f siz);

#endif