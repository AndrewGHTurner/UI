#include "CallBack.h"
#include "UI.h"

UI* Callback::ui = nullptr;

Callback::Callback(void (*onClickFunk)(void*), void* p)
{
	id = ui->newID();
	function = onClickFunk;
	param = p;
}


void Callback::setParam(void* p)
{
	param = p;
}


