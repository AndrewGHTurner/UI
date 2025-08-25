#ifndef CALLBACK_H
#define CALLBACK_H

#include <memory>
#include "UI_DLL_Interface.h"
using namespace std;

class UI;
//Callback id - unique ID of the callback which allows it to be removed from the button etc at a later time
class UI_API CallBack {
protected:
	void* param = nullptr;
	void (*function)(void*);
	
public:
	static UI* ui;
	int id;
	bool isScrollCallback = false; //indicates if this callback is for a scroll event
	CallBack(void (*onClickFunk)(void*), void* p, bool scroll = false);

	inline void run()
	{
		function(param);
	}
	void setParam(void* p);
	void* getParam();
	~CallBack();

};

template <typename T>
unique_ptr<CallBack> makeCallBack(void (*onClickFunk)(T*), T* p)
{
	return make_unique<CallBack>(
		reinterpret_cast<void(*)(void*)>(onClickFunk),
		static_cast<void*>(p),
		false
	);
}

template <typename T>
unique_ptr<CallBack> makeScrollCallBack(void (*onClickFunk)(tuple<T*, int>), T* p)
{
	return make_unique<CallBack>(
		reinterpret_cast<void(*)(void*)>(onClickFunk),
		new tuple<void*, int>(static_cast<void*>(p), 0),
		true//the int will be set to the scroll delta when the ui handles the events
	);
}

using CallBackPtr = unique_ptr<CallBack>;

#endif // !CALLBACK_H

