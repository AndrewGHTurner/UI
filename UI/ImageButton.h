#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include "InteractiveFluent.h"
class Branch;

namespace internal {
	class UI_API ImageButton : public InteractiveFluent<ImageButton, Branch> {
		Texture imageTexture;
	public:
		ImageButton(string imagePath);
		void preDraw() override;
	};
}

using ImageButtonPtr = std::unique_ptr<class internal::ImageButton>;

ImageButtonPtr UI_API ImageButton(string labelText);

#endif // IMAGE_BUTTON_H
