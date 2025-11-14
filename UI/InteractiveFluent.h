#ifndef INTERACTIVE_FLUENT_H
#define INTERACTIVE_FLUENT_H
#include "UI.h"
/**
* @brief A fluent API which holds all of the methods for registerring interactivity for UI elements.
*/
template<typename Derived, typename base>
class InteractiveFluent: public base{
public:
	using base::base;//inherit base constructors
	Derived& onClickLeftDown(function<void()> lambda)
	{
		UI* ui = UI::getInstance();
		ui->addLeftDown(lambda, static_cast<Derived*>(this)->id);
		return static_cast<Derived&>(*this);
	}

	Derived& onClickLeftDown(function<void()> lambda, int& lambdaID)
	{
		UI* ui = UI::getInstance();
		lambdaID = ui->addLeftDown(lambda, static_cast<Derived*>(this)->id);
		return static_cast<Derived&>(*this);
	}

	Derived& onClickLeftUp(function<void()> lambda, bool allowSlideOff = false)
	{
		UI* ui = UI::getInstance();
		ui->addLeftUp(lambda, static_cast<Derived*>(this)->id, allowSlideOff);
		return static_cast<Derived&>(*this);
	}
};
#endif