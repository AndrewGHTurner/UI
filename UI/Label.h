#ifndef LABEL_H
#define LABEL_H

#include "EText.h"
#include <memory>
#include "Leaf.h"
#include "ETextContainer.h"
#include "UI_DLL_Interface.h"
#include "InteractiveFluent.h"

namespace internal {
	class UI_API Label : public InteractiveFluent<Label, ETextContainer>
	{

	public:
		Label(string initialText, Vector2f origin, Vector2f siz);
		Label(string initialText);
		//overrides
		virtual void resizeText() override;
		//getters
		TextJustification getTextJustification();
		Color getColour();
		//fluent API
		Label& setColour(Color c);
		Label& setTextJustification(TextJustification justification);
		Label& setText(string newText);
		
	private:
		Color colour; // Colour of the label
	};
}

using LabelPtr = std::unique_ptr<class internal::Label>;

LabelPtr UI_API Label(string initialText);


#endif // !LABEL_H
