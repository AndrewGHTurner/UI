#include "Page.h"
#include "PageSwitcher.h"
#include "HorizontalProportionalSpacedBar.h"
#include "ColouredBox.h"
#include "ColouredButton.h"

class Page2 : public Page {
private:

public:
	int page1ID;
	PageSwitcher& pageSwitcher; // Reference to the PageSwitcher to switch back to Page1
	Page2(PageSwitcher& pageSwitcher, int page1ID) : pageSwitcher(pageSwitcher){
		this->page1ID = page1ID;
	}
	void createTree() override
	{
		unique_ptr<HorizontalProportionalSpacedBar>horBar = make_unique<HorizontalProportionalSpacedBar>(ui->getOrigin(), ui->getSize());
		unique_ptr<ColouredBox> box1 = make_unique<ColouredBox>(Color::Green);
		horBar->add(move(box1), 10);
		unique_ptr<VerticalScroll> verticalScroll = make_unique<VerticalScroll>();
		unique_ptr<ColouredBox> box2 = make_unique<ColouredBox>(Color::Black);
		verticalScroll->add(move(box2));
		ColouredButton btn1(Color::Red);
		void* u = 0;
		btn1.onClick(makeCallBack(switchToPage1, this), *UI::ui);
		verticalScroll->add(btn1);
		unique_ptr<ColouredBox> box3 = make_unique<ColouredBox>(Color::Black);
		verticalScroll->add(move(box3));
		horBar->add(move(verticalScroll), 10);
		unique_ptr<ColouredBox> box4 = make_unique<ColouredBox>(Color::Black);
		horBar->add(move(box4), 10);
		treeRoot = move(horBar);
	}

	static void switchToPage1(Page2* page2) {
		page2->pageSwitcher.showPage(page2->page1ID);
	}
};