#ifndef VERTICAL_SCROLL_H
#define VERTICAL_SCROLL_H

#include "Branch.h"
#include <SFML/OpenGL.hpp>
#include "UI_DLL_Interface.h"
#include "UI.h"

namespace internal {
	class UI_API Scroll : public Branch {
	private:
		Vector2f scrollOffset;
	public:
		Scroll();

		void preDraw() override;

		void postDraw() override;

		void add(unique_ptr<TreeNode> child) = delete;

		void setLayout(unique_ptr<Branch> layout);

		void calcPositions() override;

		void incrementOffset(int delta);
	};
}

using ScrollPtr = unique_ptr<internal::Scroll>;

ScrollPtr UI_API Scroll();

#endif