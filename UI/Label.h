#ifndef LABEL_H
#define LABEL_H

#include "EText.h"
#include <memory>
#include "Leaf.h"
#include "ETextContainer.h"
#include "UI_DLL_Interface.h"

namespace internal {
	class UI_API Label : public ETextContainer
	{

	public:
		Label(string initialText, Vector2f origin, Vector2f siz);
		Label(string initialText);
		void setColour(Color c);
		void setTextJustification(TextJustification justification);
		TextJustification getTextJustification();
		void resizeText() override;
		void setText(string newText);
		Color getColour();
	private:
		Color colour; // Colour of the label
	};
}

using LabelPtr = std::unique_ptr<class internal::Label>;

LabelPtr UI_API Label(string initialText);


#endif // !LABEL_H
