#include "LabelledCheckBox.h"

internal::LabelledCheckBox::LabelledCheckBox(string labelText) : Branch()
{
	CheckBoxPtr checkBoxPtr = ::CheckBox();
	checkBox = checkBoxPtr.get();
	unique_ptr<Label> labelPtr = make_unique<Label>(labelText);
	label = labelPtr.get();
	add(move(checkBoxPtr));//the two child elemets need adding as labelled checkbox is effectively a layout
	add(move(labelPtr));
}

void internal::LabelledCheckBox::calcPositions()
{
	//the checkbox should occupy a square area on the right side of the layout with the rest of the are being occupied by the label
	Vector2f checkBoxSize = Vector2f(size.y, size.y);
	Vector2f checkBoxOrigin = Vector2f(antiOrigin.x - size.y, origin.y);
	checkBox->setOrigin(checkBoxOrigin);
	checkBox->setSize(checkBoxSize);
	label->setOrigin(origin);
	Vector2f labelSize = Vector2f(size.x - size.y, size.y);
	label->setSize(labelSize);
}

LabelledCheckBoxPtr LabelledCheckBox(string label)
{
	return make_unique<internal::LabelledCheckBox>(label);
}