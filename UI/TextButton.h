#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "EText.h"
#include "Facade.h"
#include <memory>
#include "Label.h"
#include "CallBack.h"
#include "UI.h"
#include "TreeNode.h"

class TextButton : public Facade
{	
public:
	TextButton(string initialText)
	{
		unique_ptr<Label> label = make_unique<Label>(initialText);	
		rootNode = unique_ptr<TreeNode>(move(label));
	}

	unique_ptr<TreeNode> getRootNodeOwnership() override
	{
		return move(rootNode);
	}

	Label* getRootNodePointer() override
	{
		return label();
	}

	TextButton& onClickLeftDown(unique_ptr<Callback> callback, UI& ui)
	{
		ui.addOnClick(move(callback), rootNode->id);
		return *this;
	}

	TextButton& onClickLeftUp(unique_ptr<Callback> callback, UI& ui)
	{
		ui.addLeftUpCallback(move(callback), rootNode->id);
		return *this;
	}

	TextButton& setColour(Color c)
	{
		label()->setColour(c);
		return *this;
	}

	TextButton& setText(string newText)
	{
		//this->text->setText(newText);
		//return *this;
	}
	string getText()
	{
		//return this->text->getText();
	}
private:
	Label* label()
	{
		return static_cast<Label*>(rootNode.get());
	}

};


#endif