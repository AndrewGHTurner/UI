#ifndef LABEL_FLUENT_H
#define LABEL_FLUENT_H

#include "Label.h"

template<typename Derived>
class LabelFluent: public internal::Label{
public:
	using internal::Label::Label;//inherit label constructors
	Derived& setText(string newText)
	{
		this->internal::Label::setText(newText);
		return static_cast<Derived&>(*this);
	}
	Derived& setColour(Color c)
	{
		this->internal::Label::setColour(c);
		return static_cast<Derived&>(*this);
	}
	Derived& setTextJustification(TextJustification justification)
	{
		this->internal::Label::setTextJustification(justification);
		return static_cast<Derived&>(*this);
	}
	Derived& setHoverColour(Color c)
	{
		this->internal::Label::setHoverColour(c);
		return static_cast<Derived&>(*this);
	}
	Derived& setTextColour(Color c)
	{
		this->internal::Label::setTextColour(c);
		return static_cast<Derived&>(*this);
	}
};

#endif