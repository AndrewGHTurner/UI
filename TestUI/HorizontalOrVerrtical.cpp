#include "ListLayoutDemoPage.h"
#include <EvenList.h>
#include "ProportionalSpacedList.h"
#include <TextButton.h>
#include "PageTypes.h"


void ListLayoutDemoPage::createTree() {

	ProportionalSpacedListPtr mainContainer = ProportionalSpacedList();
	mainContainer->setMargin(3)
		.setBackgroundColour(Color(255, 0, 255));

	EvenListPtr topBar = EvenList();
	topBar->setChildSize(-1);

	TextButtonPtr homeButton = TextButton("Home");
	homeButton->onClickLeftDown([this](EventData d) {
		this->pageSwitcher.showPage(PageTypes::PAGE_1);
		});
	topBar->add(move(homeButton));

	EvenListPtr showList = EvenList();
	TextButtonPtr changeButton = TextButton("Vertical");
	changeButton->onClickLeftDown([showListPtr = showList.get(), changeButtonPtr = changeButton.get()](EventData d) {
		if (showListPtr->isVertical()) {
			showListPtr->setHorizontal();
			changeButtonPtr->setText("Horizontal");
		}
		else {
			showListPtr->setVertical();
			changeButtonPtr->setText("Vertical");
		}
		});
	topBar->add(move(changeButton));



	
	for (int i = 0; i < 5; ++i) {
		TextButtonPtr btn = TextButton("Button " + to_string(i + 1));
		btn->setColour(Color(100 + i * 30, 100 + i * 20, 200 - i * 30));
		showList->add(move(btn));
	}

	showList->setChildSize(-1);

	mainContainer->add(move(topBar), 19);
	mainContainer->add(move(showList), 90);
	treeRoot = move(mainContainer);
}