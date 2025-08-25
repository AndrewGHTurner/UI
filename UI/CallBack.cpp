#include "CallBack.h"
#include "UI.h"

CallBack::CallBack(void (*onClickFunk)(void*), void* p, bool scroll)
{
	id = UI::getInstance()->newID();
	function = onClickFunk;
	param = p;
	isScrollCallback = scroll;
}


void CallBack::setParam(void* p)
{
	param = p;
}

void* CallBack::getParam()
{
	return param;
}

CallBack::~CallBack()
{
	if (isScrollCallback && param)
	{
		delete static_cast<tuple<void*, int>*>(param);
		param = nullptr;
	}
}


