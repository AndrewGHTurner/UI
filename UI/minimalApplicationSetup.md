# Minimal Application Setup

Here are the steps to set up a minimal application:

1. Add the UI library to your project. Instructions [here](/waysToUse.md).]
2. main.cpp:

```
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "FirstPage.h"
#include "PageSwitcher.h"

using namespace std;
using namespace sf;


int main()

{

	Vector2u screenSize(700, 700);
	RenderWindow window(VideoMode(screenSize), "Mandelbrot");

	UI* ui = UI::initInstance(window);

    
	Vector2f UIOrigin(0, 0);
	Vector2f UISize(700, 700);
	ui->setOrigin(UIOrigin);
	ui->setSize(UISize);

	PageSwitcher pageSwitcher(*ui);
	PagePtr FirstPage = make_unique<FirstPage>();
	pageSwitcher.addPage(move(FirstPage), 0);

	pageSwitcher.showPage(0);


	while (window.isOpen())
	{
		ui->runUI(window);
	}
	return 0;
}
```
3. FirstPage.h
```
#include "Page.h"
#include <EvenList.h>
#include <TextButton.h>
#include <ReservedArea.h>

class FirstPage : public Page {
public:
	FirstPage()
	{

	}
	void createTree() override
	{
		UI* ui = UI::getInstance();

		EvenListPtr list = EvenList();
		list->setChildSize(-1);
		list->setBackgroundColour(Color(51, 51, 204));
		list->setVertical();

		ReservedAreaPtr area = ReservedArea();
		TextButtonPtr button = TextButton("First Button");
		button->setColour(Color(77, 77, 255))

			.setHoverColour(Color(102, 102, 255))
			.setTextColour(Color::White);
		ReservedAreaPtr area2 = ReservedArea();

		button->onClickLeftDown([h = button.get()](EventData data) {
			cout << "Button Clicked!" << endl;
			});

		list->add(move(area));
		list->add(move(button));
		list->add(move(area2));

		list->setBackgroundColour(Color(51, 51, 204));

		treeRoot = move(list);
	}
};
```