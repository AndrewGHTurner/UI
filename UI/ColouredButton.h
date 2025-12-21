#ifndef COLOURED_BUTTON_H
#define COLOURED_BUTTON_H

#include "ColouredBox.h"
#include "ui.h"
#include "Facade.h"
#include <memory>

#include "UI_DLL_Interface.h"

using namespace std;

class UI_API ColouredButton : public Facade
{
private:

public:
	ColouredButton(const ColouredButton&) = delete;             // disable copy constructor
	ColouredButton& operator=(const ColouredButton&) = delete;  // disable copy assignment
	ColouredButton(ColouredButton&&) noexcept = default;        // enable move constructor
	ColouredButton& operator=(ColouredButton&&) noexcept = default; // enable move assignment
	ColouredButton(Color c);

	unique_ptr<TreeNode> getRootNodeOwnership() override;

	ColouredBox* getRootNodePointer() override;

	ColouredButton& onClick(function<void(EventData d)> lambda);

	ColouredButton& setColor(Color c);

	ColouredButton& setSize(Vector2f siz);

	Color getColor();

	int getID();
private:
    inline ColouredBox* colouredBox()  
    {  
		return static_cast<ColouredBox*>(rootNode.get());
    }
};

#endif