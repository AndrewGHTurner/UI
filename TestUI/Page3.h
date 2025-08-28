#ifndef PAGE3_H
#define PAGE3_H


#include "Page.h"
#include "UI.h"
#include "HorizontalSplitter.h"
#include "ColouredButton.h"
#include "PageSwitcher.h"
#include "PageTypes.h"

class Page3 : public Page {
public:
	Page3(PageSwitcher& pageSwitcher) : pageSwitcher(pageSwitcher) {

	}
	void createTree() override
	{
		UI* ui = UI::getInstance();
		ColouredButton btn1(Color::Red);
		btn1.onClick([this]() {
			this->pageSwitcher.showPage(PageTypes::PAGE_1); // Assuming Page1 has ID 0
			});

		ColouredButton btn2(Color::Green);
		btn2.onClick([this]() {
			cout << "you clicked me!" << endl;
			});

		ColouredButton btn3(Color::Blue);
		btn3.onClick([this]() {
			this->pageSwitcher.showPage(PageTypes::PAGE_2); // Assuming Page2 has ID 1
			});

		HorizontalSplitterPtr splitter = HorizontalSplitter(ui->getOrigin(), ui->getSize());
		splitter->add(btn1, 30);
		splitter->add(btn2, 40);
		splitter->add(btn3, 30);

		treeRoot = move(splitter);

	}
private:
	PageSwitcher& pageSwitcher;
};

#endif
