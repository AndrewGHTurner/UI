#include "ListLayoutDemoPage.h"
#include <EvenList.h>
#include "ProportionalSpacedList.h"
#include <TextButton.h>
#include "PageTypes.h"


void ListLayoutDemoPage::createTree() {

	ProportionalSpacedListPtr mainContainer = ProportionalSpacedList();

	EvenListPtr topBar = EvenList();

	TextButtonPtr homeButton = TextButton("Home");
	homeButton->onClickLeftDown([this]() {
		this->pageSwitcher.showPage(PageTypes::PAGE_1);
		});
	topBar->add(move(homeButton));

	EvenListPtr showList = EvenList();
	TextButtonPtr changeButton = TextButton("Vertical");
	changeButton->onClickLeftDown([showListPtr = showList.get(), changeButtonPtr = changeButton.get()]() {
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

	mainContainer->add(move(topBar), 10);
	mainContainer->add(move(showList), 90);
	treeRoot = move(mainContainer);
}