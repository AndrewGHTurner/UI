#ifndef LABELLED_CHECKBOX_H
#define LABELLED_CHECKBOX_H

#include "UI_DLL_Interface.h"
#include "Branch.h"
#include "CheckBox.h"
#include "Label.h"
#include <memory>

namespace internal {
	class UI_API LabelledCheckBox : public Branch
	{
	public:
		LabelledCheckBox(string label);
		internal::CheckBox* checkBox;
		Label* label;
		void calcPositions() override;

	};
}

using LabelledCheckBoxPtr = unique_ptr<internal::LabelledCheckBox>;

LabelledCheckBoxPtr UI_API LabelledCheckBox(string label);

#endif