
#include "HorizontalSplitter.h"
#include "UI.h"

internal::HorizontalSplitter::HorizontalSplitter(Vector2f origin, Vector2f siz) : Branch(origin, siz) {
}
internal::HorizontalSplitter::HorizontalSplitter() : Branch() {
}

void internal::HorizontalSplitter::add(unique_ptr<TreeNode> child, int proportion)
{
	
	if (children.size() == 0) {
		this->add(move(child));
	}
	else
	{
		//add a splitter handle before adding the new child
		this->add(move(child));
	}

	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
}

void internal::HorizontalSplitter::add(Facade& child, int proportion)
{
	if (children.size() == 0) {
		this->add(child);
	}
	else
	{
		//add a splitter handle before adding the new child
		addHandle();
		this->add(child);
	}

	proportions.resize(children.size(), 0);//make sure that the proportions vector length matches the child vector length
	proportions.back() = proportion;
	totalProportion += proportion;
	
}

/**
* @note could factor this algorithm out as horizontal splitter also uses it
*/
void internal::HorizontalSplitter::calcPositions()
{
	int childXCoord = origin.x;
	for (int c = 0; c < children.size(); c++)
	{
		if (c % 2 == 1) // if the index is odd, it's a handle
		{
			Vector2f childOrigin(childXCoord, origin.y);
			Vector2f childSize(handleWidth, size.y);
			children[c]->setOrigin(childOrigin);
			children[c]->setSize(childSize);
			childXCoord += handleWidth;
			continue; // skip to the next iteration
		}
		unique_ptr<TreeNode>& child = children[c];
		Vector2f childOrigin(childXCoord, origin.y);
		float childWidthProportion = static_cast<float>(proportions[c]) / static_cast<float>(totalProportion);
		Vector2f childSize(childWidthProportion * size.x, size.y);
		child->setOrigin(childOrigin);
		child->setSize(childSize);
		childXCoord += childSize.x;
	}
	//	setRecalcNeededFalse();
	//	setRedrawNeededTrue();
}

void internal::HorizontalSplitter::addHandle()
{
	unique_ptr<TreeNode> handle = handleBuilder();
	//register lambdas to make it draggable
	UI* ui = UI::getInstance();

	ui->addLeftDown([handlePtr = handle.get()](void) {
		cout << "handle clicked" << endl;
		}, handle->id);

	//add the handle to the end of the children vector
	children.push_back(move(handle));
}

UI_API HorizontalSplitterPtr HorizontalSplitter() {
	return make_unique<internal::HorizontalSplitter>();
}

UI_API HorizontalSplitterPtr HorizontalSplitter(Vector2f origin, Vector2f siz) {
	return make_unique<internal::HorizontalSplitter>(origin, siz);
}