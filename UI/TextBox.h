#ifndef TEXT_BOX_H
#define TEXT_BOX_H


#include "UI_DLL_Interface.h"
#include "ETextContainer.h"
#include "Animation.h"
class Leaf;
using namespace std;



namespace internal {
	class UI_API TextBox : public Animation, public ETextContainer {
	private:
		bool editable = true;
	public:
		TextBox(Font& font, Vector2f origin, Vector2f siz, string initialText);

		TextBox(string initialText);

		TextBox(string initialText, bool isEditable);

		void setCurrentCharIndex(int index);

		bool drawAnimation();

		bool removeAnimation();

		TextBox(const TextBox&) = delete;  // Prevent copying

		void resizeText() override;
		void setText(string newText);
		string getText();
		void setColour(Color c);
		void setEditable(bool isEditable);

		bool isEditable() const { return editable; }

		static void scrollText(tuple<TextBox*, int> param);

	};
}
/**
* @brief TextBox wrapped in a unique pointer to allow for more readable API
*/
using TextBoxPtr = std::unique_ptr<class internal::TextBox>;

/**
* @brief free function to act as the TextBox's constructor... the real constructor is hidden in the internal namespace
*/
TextBoxPtr UI_API TextBox(string initialText);


#endif