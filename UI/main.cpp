//SFML .dlls needed for this to work
/*
DESIGN CHOICES
	- per widget renderring... each Leaf object has its own vertex array... hybrid with dirty flag to allow for animations
	- UI can be event driven rendered to a rendertexture which is then rendered over other content
	- hover, click etc functionality will be held in a datastructure (unordered_map<int, vector<Callback>>) external to the ui tree. this is queried using the objectID
	- borders done with their own components that are above their contents in the UI tree. The border component will need a branch to hold the UI leaf and the border leaf.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "HorizontalSpacedBar.h"
#include "HorizontalProportionalSpacedBar.h"

#include "UI.h"
#include "ColouredButton.h"
#include "ButtonFactory.h"
using namespace std;
using namespace sf;
using namespace ButtonBuilders;

void g(void*) {
	cout << "clicked";
}

int height = 10;
int width = 10;
void incrementSize(void* param) {
	cout << "clicked 2" << endl;
	//Button* b = (Button*)param;
	//height += 10;
	//width += 10;
	//b->setSize(Vector2f(width, height));
}

void changeColor(ColouredBox* b)
{
	ColouredBox* box = (ColouredBox*)b;
	if (box->colour == Color::Blue)
	{
		box->setColour(Color::Red);
	}
	else {
		box->setColour(Color::Blue);
	}
}

void changeColourBtn(ColouredButton* button)
{
	if (button->getColor() == Color::Blue)
	{
		button->setColor(Color::Red);
	}
	else {
		button->setColor(Color::Blue);
	}
}

RenderTexture* Leaf::screenTexture = nullptr;
RenderTexture* EText::screenTexture = nullptr;
RenderWindow* EText::window = nullptr;


int main()
{
	UI ui = UI();
	TreeNode::ui = &ui;


	RenderWindow window(VideoMode({ 700, 700 }), "Mandelbrot");
	EText::window = &window;
	RenderTexture texture(Vector2u(700, 700), {});
	Leaf::setTexture(&texture);
	EText::screenTexture = &texture;
	window.setFramerateLimit(10);



	//ButtonBuilders::BuildColouredButton::ui = ui;
	Callback::ui = &ui;


	Vector2f UIOrigin(0, 0);
	Vector2f UISize(700, 700);
	ui.setOrigin(UIOrigin);
	ui.setSize(UISize);
	

	Vector2f o(30, 30);
	Vector2f s(250, 200);







	Vector2f buttonOrigin = Vector2f(30, 30);
	Vector2f buttonSize = Vector2f(40, 30);
	//Button* gh = ui.addButton(buttonOrigin, buttonSize, &h);

	//ui.addOnClick(g, nullptr, gh->id);

	//h.add(gh);
	//gh->setColor(Color::Red);

	Vector2f buttonOrigin2 = Vector2f(90, 90);
	Vector2f buttonSize2 = Vector2f(40, 30);
	unique_ptr<TextBox> j = ui.addButton(buttonOrigin2, buttonSize2, "hello");


	j->r();

	//ui.addAnimation(j);
	Callback c(incrementSize, nullptr);
	ui.addOnClick(c, j->id);//WOUDL NEED TO MAKE A FOX

	//create the scroll area
	unique_ptr<VerticalScroll> verticalScroll = make_unique<VerticalScroll>(&ui, Vector2f(200, 400), Vector2f(200, 200));

	ColouredButton btn1(Color::Yellow);
	Callback c1 = makeCallBack(changeColourBtn, &btn1);
	btn1.onClick(c1, ui);
	verticalScroll->add(btn1);

	ColouredButton btn2(Color::Black);
	Callback c2 = makeCallBack(changeColourBtn, &btn2);
	btn2.onClick(c2, ui);
	verticalScroll->add(btn2);

	ColouredButton btn3(Color::Blue);
	Callback c3 = makeCallBack(changeColourBtn, &btn3);
	btn3.onClick(c3, ui);
	verticalScroll->add(btn3);

	ColouredButton btn4(Color::Magenta);
	Callback c4 = makeCallBack(changeColourBtn, &btn4);
	btn4.onClick(c4, ui);
	verticalScroll->add(btn4);

	verticalScroll->add(move(j));

	ColouredButton btn5(Color::Cyan);
	Callback c5 = makeCallBack(changeColourBtn, &btn5);
	btn5.onClick(c5, ui);
	verticalScroll->add(btn5);

	unique_ptr<HorizontalProportionalSpacedBar>ggg = make_unique<HorizontalProportionalSpacedBar>(ui.getOrigin(), ui.getSize());

	ColouredButton btna(Color::Blue);
	Callback ca = makeCallBack(changeColourBtn, &btna);
	btna.onClick(ca, ui);

	ColouredButton btnb(Color::Blue);
	Callback cb = makeCallBack(changeColourBtn, &btnb);
	btnb.onClick(cb, ui);

	ggg->add(btna, 20);
	ggg->add(move(verticalScroll), 50);
	ggg->add(btnb, 20);

	ui.add(move(ggg));

	
	while (window.isOpen())
	{
		bool displayNeeded = false;
		while (std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())//can definitly fiddle with the ordering and else if these if statements to get better performamce(minute though)
			{
				window.close();
			}
			if (event->is<Event::Resized>())
			{
				auto resized = event->getIf<sf::Event::Resized>();
				if (resized) {
					//update the SFML view to match the new window size
					float width = static_cast<float>(resized->size.x);
					float height = static_cast<float>(resized->size.y);
					sf::View view(sf::FloatRect(Vector2f(0.f, 0.f), Vector2f(width, height)));
					window.setView(view);
					

					displayNeeded = true;

					// 2. Notify your UI system of the new size
				//	ui.updateLayout(newSize.x, newSize.y);
				}
			}
			if (event->getIf<Event::MouseButtonPressed>())
			{
				ui.leftDownAt(Mouse::getPosition(window));
			}
			if (auto textEvent = event->getIf<Event::TextEntered>())
			{
				char newChar = static_cast<char>(textEvent->unicode);
				ui.handleTypeEvent(newChar);
			}
			if (event->getIf<Event::KeyPressed>())
			{
				auto keyEvent = event->getIf<Event::KeyPressed>();
				switch (keyEvent->code)
				{
				case Keyboard::Key::Up:
					ui.handleArrowEvent(ArrowDirection::UP);
					break;
				case Keyboard::Key::Left:
					ui.handleArrowEvent(ArrowDirection::LEFT);
					break;
				case Keyboard::Key::Right:
					ui.handleArrowEvent(ArrowDirection::RIGHT);
					break;
				case Keyboard::Key::Down:
					ui.handleArrowEvent(ArrowDirection::DOWN);
				}
			}
		}
		//window.clear();
		//window.draw(shape);
		ui.drawUI(window, displayNeeded);
		//window.display();
	}
	return 0;
}