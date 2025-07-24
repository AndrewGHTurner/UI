#ifndef ETEXT_CONTAINER_H
#define ETEXT_CONTAINER_H

#include <memory>
#include "EText.h"

class ETextContainer
{
	
public:
	virtual void resizeText() = 0;
	unique_ptr<EText> text;
};

#endif