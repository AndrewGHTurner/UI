#ifndef PAGE3_H
#define PAGE3_H


#include "Page.h"
#include "UI.h"
#include "HorizontalSplitter.h"
#include "ColouredButton.h"
#include "PageSwitcher.h"
#include "PageTypes.h"
#include "ReservedArea.h"

#include "HorizontalExpanderBar.h"

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

		//ColouredButton btn2(Color::Green);
		//btn2.onClick([this]() {
		//	cout << "you clicked me!" << endl;
		//	});

		unique_ptr<ReservedArea> btn2 = make_unique<ReservedArea>();


		Vector2f o = btn2->getOrigin();

		sf::CircleShape shape(50.f);

		// set the shape color to green
		shape.setFillColor(sf::Color(100, 250, 50));
		shape.setPosition(o);

		ui->window.draw(shape);
		ui->window.display();



		ColouredButton btn3(Color::Magenta);
		btn3.onClick([this]() {
			cout << "you clicked me Too!" << endl;
			});

		ColouredButton btn4(Color::Blue);
		btn4.onClick([this]() {
			this->pageSwitcher.showPage(PageTypes::PAGE_2); // Assuming Page2 has ID 1
			});

		HorizontalSplitterPtr splitter = HorizontalSplitter();
		splitter->add(btn1, 30);
		splitter->add(move(btn2), 10);
		splitter->add(btn3, 30);
		splitter->add(btn4, 30);

		ColouredButton btn5(Color::Blue);
		btn5.onClick([]() {
			cout << "you clicked the menu" << endl;
			}).setSize(Vector2f(50, 50));

		ColouredButton btn6(Color(155, 0, 255));
		btn6.onClick([]() {
			cout << "you clicked the menu on this side!!!" << endl;
			}).setSize(Vector2f(50, 50));

		unique_ptr<HorizontalExpanderBar> expanderBar = make_unique<HorizontalExpanderBar>(ui->getOrigin(), ui->getSize());

		expanderBar->add(btn5, SizePolicy::FIXED_SIZE);
		expanderBar->add(move(splitter), SizePolicy::EXPANDER);
		expanderBar->add(btn6, SizePolicy::FIXED_SIZE);

		treeRoot = move(expanderBar);

	}
private:
	PageSwitcher& pageSwitcher;
};

#endif
