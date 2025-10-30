#include "pch.h"
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
	Vector2f checkBoxSize;
	Vector2f labelSize;
	Vector2f checkBoxOrigin;
	if (size.y < size.x)//if the element is a horizontal rectangle
	{
		labelSize = Vector2f(size.x - size.y, size.y);
		checkBoxSize = Vector2f(size.y, size.y);
		checkBoxOrigin = Vector2f(antiOrigin.x - size.y, origin.y);
	}
	else {//if the element is a vertical rectangle ... cannot display the label properly ... UIs should not use this element in this way
		labelSize = Vector2f(0, 0);
		checkBoxSize = Vector2f(size.x, size.x);
		checkBoxOrigin = Vector2f(origin.x, (size.y - checkBoxSize.y) / 2);
	}
	
	
	checkBox->setOrigin(checkBoxOrigin);
	checkBox->setSize(checkBoxSize);
	label->setOrigin(origin);
	
	label->setSize(labelSize);
}

LabelledCheckBoxPtr LabelledCheckBox(string label)
{
	return make_unique<internal::LabelledCheckBox>(label);
}