#ifndef CHECKBOX_H
#define CHECKBOX_H	

#include "UI_DLL_Interface.h"
#include "Leaf.h"
#include "memory"
#include <functional>
using namespace std;
namespace internal {
	class UI_API CheckBox : public Leaf
	{
	public:
		bool checked = false;
		CheckBox();
		void setChecked(bool c);
		void toggle(bool withLeftClick = true);
		void updateVerticesPosition() override;
		void onToggle(std::function<void()> g);
	private:
		void unCheck();
		void check(Vector2f origin, Vector2f antiOrigin);
	};
}

using CheckBoxPtr = unique_ptr<internal::CheckBox>;

UI_API CheckBoxPtr CheckBox();
#endif // !CHECKBOX_H
