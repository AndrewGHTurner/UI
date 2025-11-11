#ifndef TEXT_JUSTIFICATION_PAGE_H
#define TEXT_JUSTIFICATION_PAGE_H

#include "Page.h"

#include "PageSwitcher.h"

class TextJustificationPage : public Page {
private:
	PageSwitcher& pageSwitcher;
public:
	TextJustificationPage(PageSwitcher& switcher) : pageSwitcher(switcher) {}
	void createTree() override
	{
		ProportionalSpacedListPtr mainContainer = ProportionalSpacedList();
		//title bar and home button
		EvenListPtr topBar = EvenList();
		topBar->setChildSize(-1);

		TextButtonPtr homeButton = TextButton("Home");
		homeButton->onClickLeftDown([this]() {
			this->pageSwitcher.showPage(PageTypes::PAGE_1);
			});
		topBar->add(move(homeButton));
		//three EvenLists with buttons to change the text justification of a label
		//top
		EvenListPtr topLabelList = EvenList();
		topLabelList->setChildSize(-1);
		topLabelList->setHorizontal();
		LabelPtr topLabel = Label("LEFT");
		topLabel->setColour(Color(50, 150, 50));
		topLabel->setTextJustification(TextJustification::LEFT);
		TextButtonPtr topButton = TextButton("Change Justification");
		topButton->setColour(Color::Red)
			.setPressedColour(Color::Green)
			.onClickLeftDown([topLabel = topLabel.get()]() {
			//cycle through justifications
			if (topLabel->getTextJustification() == TextJustification::LEFT) {
				topLabel->setText("CENTER");
				topLabel->setTextJustification(TextJustification::CENTER);
			}
			else if (topLabel->getTextJustification() == TextJustification::CENTER) {
				topLabel->setText("RIGHT");
				topLabel->setTextJustification(TextJustification::RIGHT);
			}
			else {
				topLabel->setText("LEFT");
				topLabel->setTextJustification(TextJustification::LEFT);
			}
				});
		topLabelList->add(move(topLabel));
		topLabelList->add(move(topButton));
		//middle
		EvenListPtr middleLabelList = EvenList();
		middleLabelList->setChildSize(-1);
		middleLabelList->setHorizontal();
		LabelPtr middleLabel = Label("CENTER");
		middleLabel->setColour(Color(50, 150, 50));
		middleLabel->setTextJustification(TextJustification::CENTER);
		TextButtonPtr middleButton = TextButton("Change Justification");
		middleButton->setColour(Color::Red)
			.setPressedColour(Color::Green)
			.onClickLeftDown([middleLabel = middleLabel.get()]() {
			//cycle through justifications
			if (middleLabel->getTextJustification() == TextJustification::LEFT) {
				middleLabel->setText("CENTER");
				middleLabel->setTextJustification(TextJustification::CENTER);
			}
			else if (middleLabel->getTextJustification() == TextJustification::CENTER) {
				middleLabel->setText("RIGHT");
				middleLabel->setTextJustification(TextJustification::RIGHT);
			}
			else {
				middleLabel->setText("LEFT");
				middleLabel->setTextJustification(TextJustification::LEFT);
			}
				});
		middleLabelList->add(move(middleLabel));
		middleLabelList->add(move(middleButton));
		//bottom
		EvenListPtr bottomLabelList = EvenList();
		bottomLabelList->setChildSize(-1);
		bottomLabelList->setHorizontal();
		LabelPtr bottomLabel = Label("RIGHT");
		bottomLabel->setColour(Color(50, 150, 50));
		bottomLabel->setTextJustification(TextJustification::RIGHT);
		TextButtonPtr bottomButton = TextButton("Change Justification");
		bottomButton->setColour(Color::Red)
			.setPressedColour(Color::Green)
			.onClickLeftDown([bottomLabel = bottomLabel.get()]() {
			//cycle through justifications
			if (bottomLabel->getTextJustification() == TextJustification::LEFT) {
				bottomLabel->setText("CENTER");
				bottomLabel->setTextJustification(TextJustification::CENTER);
			}
			else if (bottomLabel->getTextJustification() == TextJustification::CENTER) {
				bottomLabel->setText("RIGHT");
				bottomLabel->setTextJustification(TextJustification::RIGHT);
			}
			else {
				bottomLabel->setText("LEFT");
				bottomLabel->setTextJustification(TextJustification::LEFT);
			}
				});

		bottomLabelList->add(move(bottomLabel));
		bottomLabelList->add(move(bottomButton));

		mainContainer->add(move(topBar), 10);
		mainContainer->add(move(topLabelList), 30);
		mainContainer->add(move(middleLabelList), 30);
		mainContainer->add(move(bottomLabelList), 30);
		treeRoot = move(mainContainer);
	}
};


#endif // TEXT_JUSTIFICATION_PAGE_H
