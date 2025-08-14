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
#include "CallBack.h"
#include <tuple>
//#include "main.h"
#include "UI.h"
#include "ColouredButton.h"
#include "ButtonFactory.h"
#include "Page.h"
#include "PageSwitcher.h"
#include <Vertical.h>
#include <page1.h>
#include <page2.h>
#include <tuple>


//#include "testPage.h"

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
void addTreeNode(Vertical* branch)
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
	tuple<Branch*, int>* btnTuple = new std::tuple<Branch*, int>(branch, btn.getID());
	btn.onClick(makeCallBack(removeTreeNode, btnTuple), *UI::ui);
	branch->add(btn);
}



//RenderTexture* EText::screenTexture = nullptr;
//RenderWindow* EText::window = nullptr;


int main()
{
	Vector2u screenSize(700, 700); // Set the screen size to 700x700 pixels
	RenderWindow window(VideoMode(screenSize), "Mandelbrot");
	window.setFramerateLimit(10);

	UI ui = UI(window);

	Vector2f UIOrigin(0, 0);
	Vector2f UISize(700, 700);
	ui.setOrigin(UIOrigin);
	ui.setSize(UISize);

	PageSwitcher pageSwitcher(ui);//on the stack but may need to be on heap if functions returns
	int page1ID = pageSwitcher.newPageID(); // Create a new page ID for Page1
	int page2ID = pageSwitcher.newPageID(); // Create a new page ID for Page2
	unique_ptr<Page1> page1 = make_unique<Page1>(pageSwitcher, page2ID);



	unique_ptr<Page2> page2 = make_unique<Page2>(pageSwitcher, page1ID); // Create Page2 with a reference to PageSwitcher and Page1 ID




	pageSwitcher.setPage(page1ID, move(page1)); // Set Page1 in the PageSwitcher
	pageSwitcher.setPage(page2ID, move(page2)); // Set Page2 in the PageSwitcher
	pageSwitcher.showPage(page1ID); // Show Page1 initially



	//testPage(); // Call the testPage function from the DLL


//	testPage();

	while (window.isOpen())
	{
		ui.runUI(window);
	}
	return 0;
}