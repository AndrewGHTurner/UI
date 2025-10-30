#ifndef HORIZONTAL_SPACED_BAR
#define HORIZONTAL_SPACED_BAR
#include "Branch.h"
#include <memory>
#include "UI_DLL_Interface.h"
#include "SizePolicy.h"


/**
* @brief A horizontal layout that holds a size policy for each of its children
*/
class UI_API HorizontalExpanderBar : public Branch {
private:
	vector<uint8_t> sizePolicies;
public:
	HorizontalExpanderBar(Vector2f origin, Vector2f siz) : Branch(origin, siz) {}

	void add(Facade& facade, SizePolicy sizePolicy);

	void add(unique_ptr<TreeNode> child, SizePolicy sizePolicy);

	void calcPositions() override;
};

#endif