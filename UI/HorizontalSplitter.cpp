
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
	int totalHandleWidth = (children.size() / 2) * handleWidth;
	float totalChildWidth = size.x - totalHandleWidth;
	float childXCoord = origin.x;
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
		else {//if it is a user provided TreeNode
			unique_ptr<TreeNode>& child = children[c];
			Vector2f childOrigin(childXCoord, origin.y);
			float childWidthProportion = static_cast<float>(proportions[c]) / static_cast<float>(totalProportion);
			Vector2f childSize(childWidthProportion * totalChildWidth, size.y);
			child->setOrigin(childOrigin);
			child->setSize(childSize);
			childXCoord += childSize.x;
		}
	}
}

void internal::HorizontalSplitter::addHandle()
{
	unique_ptr<TreeNode> handle = handleBuilder();
	//register lambdas to make it draggable
	UI* ui = UI::getInstance();
	int handleIndex = children.size();//the handle hasn't yet been added to children so no need to subtract 1
	ui->addLeftDown([handlePtr = handle.get(), this, handleIndex](void) 
	{
		UI* ui = UI::getInstance();
		
		//add the drag lambda ... this is the lambda that will move the splitter handles
		dragLambdaID = ui->addMouseMovementLambda([handleIndex, this](Vector2i mousePos) {
			
			int leftMostX = children[handleIndex - 1].get()->getOrigin().x;
			int rightMostX = children[handleIndex + 1].get()->getAntiOrigin().x;
			int totalXRange = rightMostX - leftMostX;
			float totalProportion = proportions[handleIndex - 1] + proportions[handleIndex + 1];
			float n = mousePos.x - leftMostX;
			if (n < 0) {
				n = 0;
			}
			if (mousePos.x > rightMostX) {
				n = totalXRange;
			}
			float leftProp = n / totalXRange;
			float leftProportion = leftProp * totalProportion;
			if (leftProportion < 0) {
				leftProportion = 0;
			}
			float rightProportion = (1 - leftProp) * totalProportion;
			if (rightProportion < 0) {
				rightProportion = 0;
			}

			proportions[handleIndex - 1] = leftProportion;
			proportions[handleIndex + 1] = rightProportion;
			notifyRecalcNeeded();
			});

		//add the release lambda ... this lambda will remove the drag lambda and itself	
		releaseLambdaID = ui->addLeftUp([this](void)
			{
				UI* ui = UI::getInstance();
				//remove the drag lambda
				ui->removeMouseMovementLambda(dragLambdaID);
				//remove this release lambda ... itself
				ui->removeLeftUp(releaseLambdaID);
			});
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