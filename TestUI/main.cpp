//SFML .dlls needed for this to work
/*
DESIGN CHOICES
	- per widget renderring... each Leaf object has its own vertex array... hybrid with dirty flag to allow for animations
	- UI can be event driven rendered to a rendertexture which is then rendered over other content
	- hover, click etc functionality will be held in a datastructure (unordered_map<int, vector<function<void()>>) external to the ui tree. this is queried using the objectID
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
//#include "main.h"
#include "UI.h"
#include "ColouredButton.h"
#include "Page.h"
#include "PageSwitcher.h"
#include <Vertical.h>
#include "page1.h"
#include "page2.h"
#include "Page3.h"
#include <tuple>
#include "PageTypes.h"


//#include "testPage.h"

using namespace std;
using namespace sf;

void g(void*) {
	cout << "clicked";
}

int height = 10;
int width = 10;


//RenderTexture* EText::screenTexture = nullptr;
//RenderWindow* EText::window = nullptr;

#ifdef NO_CONSOLE
#define MAIN() int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
#define MAIN() int main()
#endif

MAIN()
{
	Vector2u screenSize(700, 700); // Set the screen size to 700x700 pixels
	RenderWindow window(VideoMode(screenSize), "Mandelbrot");
	window.setFramerateLimit(1);

	UI* ui = UI::initInstance(window);

	Vector2f UIOrigin(0, 0);
	Vector2f UISize(700, 700);
	ui->setOrigin(UIOrigin);
	ui->setSize(UISize);

	PageSwitcher pageSwitcher(*ui);//on the stack but may need to be on heap if functions returns

	PagePtr page1 = make_unique<Page1>(pageSwitcher);



	PagePtr page2 = make_unique<Page2>(pageSwitcher); // Create Page2 with a reference to PageSwitcher and Page1 ID

	PagePtr page3 = make_unique<Page3>(pageSwitcher); // Create Page3 with a reference to PageSwitcher


	pageSwitcher.addPage(move(page1), PageTypes::PAGE_1);
	pageSwitcher.addPage(move(page2), PageTypes::PAGE_2);
	pageSwitcher.addPage(move(page3), PageTypes::PAGE_3);
	pageSwitcher.showPage(PageTypes::PAGE_1); // Show Page1 initially



	//testPage(); // Call the testPage function from the DLL


//	testPage();

	while (window.isOpen())
	{
		ui->runUI(window);
	}
	return 0;
}