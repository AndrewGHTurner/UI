#ifndef LABEL_H
#define LABEL_H

#include "EText.h"
#include <memory>
#include "Leaf.h"
#include "ETextContainer.h"
#include "UI_DLL_Interface.h"

class UI_API Label : public ETextContainer
{

public:
	Label(string initialText, Vector2f origin, Vector2f siz);
	Label(string initialText);
	void setColour(Color c);
	void resizeText() override;
	Color getColour();
private:
	Color colour; // Colour of the label
};


#endif // !LABEL_H
