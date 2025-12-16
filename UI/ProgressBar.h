#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
#include "Leaf.h"
#include "UI_DLL_Interface.h"

namespace internal {
	class UI_API ProgressBar : public Leaf
	{
	private:
		Color backgroundColour = Color(100, 100, 100); // Default background colour
		Color barColour = Color(0, 255, 0); // Default bar colour
		float progress = 0.0f; // Progress value between 0.0 and 1.0
	public:
		ProgressBar();
		ProgressBar& setBackgroundColour(Color c);
		ProgressBar& setBarColour(Color c);
		ProgressBar& setProgress(float progress); // progress should be between 0.0 and 1.0
		float getProgress();
	};
}

using ProgressBarPtr = std::unique_ptr<class internal::ProgressBar>;

ProgressBarPtr UI_API ProgressBar();

#endif // !PROGRESS_BAR_H
