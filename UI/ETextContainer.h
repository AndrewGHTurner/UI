#ifndef ETEXT_CONTAINER_H
#define ETEXT_CONTAINER_H

#include <memory>
#include "EText.h"
#include "UI_DLL_Interface.h"
#include "Leaf.h"
class UI_API ETextContainer : public Leaf
{
	
public:
	virtual void resizeText() = 0;
	unique_ptr<EText> text;
	virtual ~ETextContainer() = default;

};

#endif