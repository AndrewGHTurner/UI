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
#include <tuple>

#include "UI.h"
#include "ColouredButton.h"
#include "ButtonFactory.h"
#include "Page.h"
#include "PageSwitcher.h"
#include "Page1.cpp"
#include "Page2.cpp"

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

void removeTreeNode(tuple<Branch*, int>* tuple)
{
	Branch* branch = get<0>(*tuple);
	int id = get<1>(*tuple);
	branch->remove(id);
	delete tuple;//Clean up the dynamically allocated memory
}
int t = 0;
void addTreeNode(VerticalScroll* branch)
{
	Color f;
	if (t == 0)
	{
		f = Color::Red;
	}
	else if (t == 1)
	{
		f = Color::Green;
	}
	else if (t == 2)
	{
		f = Color::Blue;
	}
	else if (t == 3)
	{
		f = Color::Magenta;
		t = -1;
	}
	t += 1;

	ColouredButton btn(f);
	btn.onClick(makeCallBack(removeTreeNode, new tuple<Branch*, int>(branch, btn.getID())), *UI::ui);
	branch->add(btn);
}



RenderTexture* Leaf::screenTexture = nullptr;
RenderTexture* EText::screenTexture = nullptr;
RenderWindow* EText::window = nullptr;


int main()
{
	UI ui = UI();
	TreeNode::ui = &ui;
	Page::ui = &ui;

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


	PageSwitcher pageSwitcher(ui);//on the stack but may need to be on heap if functions returns
	unique_ptr<Page1> page1 = make_unique<Page1>(pageSwitcher);
	Page1* page1Ptr = page1.get(); // Get a raw pointer to the unique_ptr
	int page1ID = pageSwitcher.addPage(move(page1));
	int page2ID = pageSwitcher.addPage(make_unique<Page2>(pageSwitcher, page1ID)); // Create Page2 with a reference to PageSwitcher and Page1 ID
	page1Ptr->setPage2ID(page2ID);
	pageSwitcher.showPage(page2ID);

	
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