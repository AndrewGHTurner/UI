#include "Page.h"
#include "PageSwitcher.h"
#include "HorizontalProportionalSpacedBar.h"
#include "ColouredBox.h"
#include "ColouredButton.h"
#include "Vertical.h"
#include "PageTypes.h"

class Page2 : public Page {
private:

public:
	int page1ID;
	PageSwitcher& pageSwitcher; // Reference to the PageSwitcher to switch back to Page1
	Page2(PageSwitcher& pageSwitcher) : pageSwitcher(pageSwitcher){
	}
	void createTree() override
	{
		UI* ui = UI::getInstance();
		HorizontalProportionalSpacedBarPtr horBar = HorizontalProportionalSpacedBar(ui->getOrigin(), ui->getSize());
		unique_ptr<ColouredBox> box1 = make_unique<ColouredBox>(Color::Green);
		horBar->add(move(box1), 10);
		VerticalPtr verticalScroll = Vertical();
		unique_ptr<ColouredBox> box2 = make_unique<ColouredBox>(Color::Black);
		verticalScroll->add(move(box2));
		ColouredButton btn1(Color::Red);
		void* u = 0;

		function<void()> switchToPage1 = [this]() {
			this->pageSwitcher.showPage(PageTypes::PAGE_1);
			};

		btn1.onClick(switchToPage1);
		verticalScroll->add(btn1);
		unique_ptr<ColouredBox> box3 = make_unique<ColouredBox>(Color::Black);
		verticalScroll->add(move(box3));
		horBar->add(move(verticalScroll), 10);
		unique_ptr<ColouredBox> box4 = make_unique<ColouredBox>(Color::Black);
		horBar->add(move(box4), 10);
		treeRoot = move(horBar);
	}
};