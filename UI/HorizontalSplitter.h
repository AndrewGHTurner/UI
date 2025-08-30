#ifndef HORIZONTAL_SPLITTER
#define HORIZONTAL_SPLITTER


#include "UI_DLL_Interface.h"
#include "Branch.h"
#include "Proportioned.h"
#include "SplitterHandle.h"
#include <functional>
#include "ColouredBox.h"

namespace internal {
	class UI_API HorizontalSplitter : public Branch, private Proportioned {
	public:
		HorizontalSplitter(Vector2f origin, Vector2f siz);
		HorizontalSplitter();

		/**@note should make an add multiple function so that the proportions vector isn't needlesly recalculated. Or have a flag
		*/
		void add(unique_ptr<TreeNode> child, int proportion);
		void add(Facade& child, int proportion);
		void calcPositions() override;
	private:
		int handleWidth = 6;
		uint32_t dragLambdaID = 0;//id of the drag lambda of the active handle(currently being dragged) Only one handle can be dragged at a time so this works
		uint32_t releaseLambdaID = 0;//id of the release lambda of the active handle
		/**
		* @brief Adds a handle to the end of the children vector.
		* @details This calls the handelBuilder to build the UI tree and registers the labmdas required to make it draggable.
		*/
		void addHandle();

		/**
		* @brief builds the UI tree of the handles. This lambda could be user provide to allow for custom handles
		*/
		function<unique_ptr<TreeNode>()> handleBuilder = []() {
			unique_ptr<ColouredBox> box = make_unique<ColouredBox>(Color::Yellow);
			return move(box);
			};
		using Branch::add;
	};
}

using HorizontalSplitterPtr = unique_ptr<internal::HorizontalSplitter>;

UI_API HorizontalSplitterPtr HorizontalSplitter();

UI_API HorizontalSplitterPtr HorizontalSplitter(Vector2f origin, Vector2f siz);

#endif