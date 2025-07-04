#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H
#include "UI.h"
#include "ColouredBox.h"
#include <memory>
using namespace std;

/*a seried of button builders that speed up development of UIs. More efficient solutions could likely be created via manually
configuring buttons. Additionally, the fluent API could be improved using a staged builder pattern*/
namespace ButtonBuilders
{
	class BuildColouredButton;
	//PLACE THIS CLASS IN THE .CPP FILE SO THAT IT ISN'T EXPOSED IN THE API
	class GetParamStage
	{
	public:

		GetParamStage(BuildColouredButton& creator, Callback& callBack, unique_ptr<ColouredBox>& colouredBox)
			: creator(creator), callBack(callBack), colouredBox(colouredBox)
		{

		}
		//this will always be the param for the callback at the end of the creator.callbacks vector
		BuildColouredButton& withParam(void* param = nullptr)
		{
			callBack.setParam(param);
			return creator;
		}

		BuildColouredButton& withSelfAsParam()
		{
			callBack.setParam(colouredBox.get());
			return creator;
		}
	private:
		
		Callback& callBack;
		unique_ptr<ColouredBox>& colouredBox;
		BuildColouredButton& creator;
	};

	
	class BuildColouredButton
	{
	private:
		
		Color buttonColour;
		Branch* branch;
		int newButtonID;
		unique_ptr<ColouredBox> colouredBox;
		UI* ui;
		vector<Callback> callbacks;
	public:
		
		BuildColouredButton(UI* ui) : ui(ui)
		{
			callbacks = vector<Callback>();
			newButtonID = ui->newID();
			colouredBox = make_unique<ColouredBox>();
		}
		BuildColouredButton& inBranch(Branch* branch)
		{
			this->branch = branch;
			return *this;
		}
		BuildColouredButton& withColour(Color colour)
		{
			buttonColour = colour;
			return *this;
		}
		GetParamStage addOnClick(void (*onClick)(void*), int* outCallBackID = nullptr)
		{
			Callback callBack(onClick, nullptr);
			if (outCallBackID)
			{
				*outCallBackID = callBack.id;
			}
			callbacks.push_back(callBack);
			return GetParamStage(*this, callbacks.back(), colouredBox);
		}
		//unique_ptr<ColouredBox> get()
		//{
		//	for (Callback callBack : callbacks)
		//	{
		//		ui->addOnClick(callBack, colouredBox.get()->id);
		//	}
		//	colouredBox->setColour(buttonColour);
		//	colouredBox->parentNode = branch;
		//	return move(colouredBox);
		//}
	};
}

class ButtonBuilder
{
public:
	UI& ui;
	ButtonBuilder(UI& givenUi) : ui(givenUi)
	{
	}

	

	//TreeNode* makeColouredButton(Color colour, void (*onClick)(void*), void* param = nullptr, Branch* container = nullptr)
	//{

	//	ColouredBox* newColoredBox = new ColouredBox(colour, container);
	//	if (param == nullptr)
	//	{
	//		param = newColoredBox;
	//	}
	//	Callback callBack(onClick, param);
	//	ui.addOnClick(callBack, newColoredBox->id);
	//	if (container != nullptr)
	//	{
	//		container->add(unique_ptr<ColouredBox>(newColoredBox));
	//	}
	//	return newColoredBox;
	//}


};



#endif