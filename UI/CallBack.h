#ifndef CALLBACK_H
#define CALLBACK_H

#include <memory>
using namespace std;

class UI;
//Callback id - unique ID of the callback which allows it to be removed from the button etc at a later time
class Callback {
protected:
	void* param = nullptr;
	void (*function)(void*);
	
public:
	static UI* ui;
	int id;
	Callback(void (*onClickFunk)(void*), void* p);

	inline void run()
	{
		function(param);
	}
	void setParam(void* p);


};

template <typename T>
unique_ptr<Callback> makeCallBack(void (*onClickFunk)(T*), T* p)
{
	return make_unique<Callback>(
		reinterpret_cast<void(*)(void*)>(onClickFunk),
		static_cast<void*>(p)
	);
}

#endif // !CALLBACK_H

