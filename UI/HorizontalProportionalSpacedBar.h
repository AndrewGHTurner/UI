#ifndef HORIZONTAL_PROPORTIONAL_SPACED_BAR
#define HORIZONTAL_PROPORTIONAL_SPACED_BAR

#include "Branch.h"
#include <memory>
#include "Facade.h"
#include "UI_DLL_Interface.h"

class UI_API HorizontalProportionalSpacedBar : public Branch {
private:
	vector<int> proportions;
	int totalProportion = 0;
public:
	HorizontalProportionalSpacedBar();
	HorizontalProportionalSpacedBar(Vector2f origin, Vector2f siz);
	using Branch::add;
	//proportion is the amount of space the widget needs... will be relative to the proportions given to other widgets
	void add(Facade& facade, int proportion);
	void add(unique_ptr<TreeNode> child, int proportion);

	void calcPositions() override;
};

#endif