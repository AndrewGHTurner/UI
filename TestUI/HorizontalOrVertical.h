#ifndef HORIZONTAL_OR_VERTICAL
#define HORIZONTAL_OR_VERTICAL

#include "Page.h"  

class HorizontalOrVertical : public Page {

public:
	HorizontalOrVertical(HorizontalOrVertical&& other) = default; // Move constructor for HorizontalOrVertical
	HorizontalOrVertical() {
	}
	void createTree() override;
};


#endif // !HORIZONTAL_OR_VERTICAL
