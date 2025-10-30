#ifndef LABELLED_CHECKBOX_H
#define LABELLED_CHECKBOX_H

#include "CheckBox.h"
#include "Label.h"

namespace internal {
	class UI_API LabelledCheckBox : public Branch
	{
	public:
		LabelledCheckBox(string label);
		internal::CheckBox* checkBox;
		internal::Label* label;
		void calcPositions() override;

	};
}

using LabelledCheckBoxPtr = unique_ptr<internal::LabelledCheckBox>;

LabelledCheckBoxPtr UI_API LabelledCheckBox(string label);

#endif