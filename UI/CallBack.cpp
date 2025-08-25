#include "CallBack.h"
#include "UI.h"

Callback::Callback(void (*onClickFunk)(void*), void* p, bool scroll)
{
	id = UI::getInstance()->newID();
	function = onClickFunk;
	param = p;
	isScrollCallback = scroll;
}


void Callback::setParam(void* p)
{
	param = p;
}

void* Callback::getParam()
{
	return param;
}

Callback::~Callback()
{
	if (isScrollCallback && param)
	{
		delete static_cast<tuple<void*, int>*>(param);
		param = nullptr;
	}
}


