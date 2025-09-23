#include "Page.h"  
#include "ColouredButton.h"  
#include "TextButton.h"
#include "HorizontalProportionalSpacedBar.h"  
#include <memory>  
#include "PageSwitcher.h"
#include "Label.h"
#include "Vertical.h"
#include "Scroll.h"
#include "PageTypes.h"
#include <functional>
#include "CheckBox.h"


class Page1 : public Page {  
private:
   // LabelColour TBpressedColour;
	//LabelColour TBreleasedColour; // Store the label and its colour for later use
    TextButtonMaker TB = TextButtonMaker();
	
public:
    PageSwitcher& pageSwitcher; // Reference to the PageSwitcher to switch back to Page
	Page1(Page1&& other) = default; // Move constructor for Page1
    Page1(PageSwitcher& pageSwitcher) : pageSwitcher(pageSwitcher){
    }

	function<void()> makeSwitchPageLambda(int pageID) {
		return [this, pageID]() {
			this->pageSwitcher.showPage(pageID);
			};
	}

	function<void()> makeChangeColourLambda(ColouredBox* button) {
		return [button]() {
			if (button->colour == Color::Cyan)
			{
				button->setColour(Color::Magenta);
			}
			else {
				button->setColour(Color::Cyan);
			}
			};
	}

   void createTree() override  
   {   
	   UI* ui = UI::getInstance();
       TextBoxPtr j = TextBox("Hello");
       void* d = nullptr;

	   function<void()> print = []() { cout << "clicked" << endl; };
       ui->addLeftDown(print, j->id);//WOUDL NEED TO MAKE A FOX  

       //create the scroll area  
	   VerticalPtr verticalScroll = Vertical();
	   verticalScroll->setMargin(4); // Set the margin between elements in the scroll area
       verticalScroll->setBackgroundColour(Color(63, 3, 153)); // Set the background colour of the scroll area

	   unique_ptr<Label> label = make_unique<Label>("first label", Vector2f(0, 0), Vector2f(200, 30));
	   verticalScroll->add(move(label));

       function<void()> addTreeNode = [branch = verticalScroll.get()]() {
           static int t;
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
           else
           {
               f = Color::Magenta;
               t = -1;
           }
           t += 1;

           ColouredButton btn(f);

           function<void()> removeTreeNode = [branch, btnID = btn.getID()]() {           
               branch->remove(btnID);
               };

           btn.onClick(removeTreeNode);
           branch->add(btn);

           };

	   //make check box
	   CheckBoxPtr checkBox = CheckBox();

       TB.createButton("Is checked?")
           .onClickLeftDown([checkBoxPtr = checkBox.get()]() {
           if (checkBoxPtr->checked) {
               cout << "Checked!" << endl;
           }
           else {
               cout << "Not checked!" << endl;
           }
               })
           .setColour(Color::Cyan)
           .setPressedColour(Color::Blue);
       verticalScroll->add(move(checkBox));
	   verticalScroll->add(TB);

       TB.createButton("Add Button")
           .onClickLeftDown(addTreeNode)
		   .setPressedColour(Color::Green) // Set the pressed colour for the button
           .setColour(Color::Yellow);      
	   verticalScroll->add(TB);

       string k = "This is a lambda";
       function<void()> l = [k]() {
		   cout << "lambda clicked " << k << endl; }; // Example lambda function

       TB.createButton("resizer")
           .setColour(Color::Red)
           .setPressedColour(Color::Blue)
		   .onClickLeftDown(l);
        
	   verticalScroll->add(TB);



       ColouredButton btn2 = ColouredButton(Color::Black);
	   function<void()> removeTreeNode = [verticalScrollPtr = verticalScroll.get(), btnID = btn2.getID()]() {
		   verticalScrollPtr->remove(btnID);
		   };
	   btn2.onClick(removeTreeNode);

       verticalScroll->add(btn2);  


       TB.createButton("Page 2")
		   .setColour(Color::Cyan)
		   .setPressedColour(Color::Magenta)
		   .onClickLeftDown(makeSwitchPageLambda(PageTypes::PAGE_2));
       verticalScroll->add(TB);  

	   TB.createButton("Page 3")
		   .setColour(Color::Cyan)
		   .setPressedColour(Color::Magenta)
		   .onClickLeftUp(makeSwitchPageLambda(PageTypes::PAGE_3), true);
	   verticalScroll->add(TB);  

       ColouredButton btn4 = ColouredButton(Color::Magenta);

	   
	   btn4.onClick(makeChangeColourLambda(btn4.getRootNodePointer()));

       verticalScroll->add(btn4);  

       verticalScroll->add(move(j));  

       ColouredButton btn5 = ColouredButton(Color::Cyan);
       btn5.onClick(makeChangeColourLambda(btn5.getRootNodePointer()));  



       verticalScroll->add(btn5);  

       unique_ptr<HorizontalProportionalSpacedBar>ggg = make_unique<HorizontalProportionalSpacedBar>(ui->getOrigin(), ui->getSize());  

       ColouredButton btna(Color::Blue);  
       btna.onClick(makeChangeColourLambda(btna.getRootNodePointer()));

       VerticalPtr vert = Vertical();//make_unique<Vertical>(Vector2f(0, 0), Vector2f(200, 200));

	   unique_ptr<Scroll> scroll = make_unique<Scroll>();
       scroll->setBackgroundColour(Color::Green);

       VerticalPtr vert2 = Vertical();
	   vert2->setMargin(4); // Set the margin between elements in the vertical scroll area


	   int vert2Height = 0; // Initialize the height of the vertical scroll area
       for (int t = 0; t < 20; t++) {
           ColouredButton btnb(Color::Blue);
           btnb.onClick(makeChangeColourLambda(btnb.getRootNodePointer()));
           vert2->add(btnb); // Add btnb to the scroll area
		   vert2Height += 40; // Increment the height for each button added
       }
	   vert2->setSize(Vector2f(200, vert2Height)); // Set the size of the vertical scroll area based on the number of buttons
	   scroll->add(move(vert2)); // Add the vertical scroll to the scroll area
       ColouredButton btny(Color::Blue);
       btny.onClick(makeChangeColourLambda(btny.getRootNodePointer()));


	   //add mouseWheel lambda to scroll area
       function<void(int)> scroller = [scrollPtr = scroll.get()](int delta) {
           scrollPtr->incrementOffset(delta);
           };
	   ui->addMouseWheelLambda(scroller, scroll->id);

       vert->add(btny); // Add btny to the vertical scroll
	   vert->add(move(scroll)); // Add the scroll area to the vertical scroll
	   


       ggg->add(move(vert), 30);  
       ggg->add(move(verticalScroll), 50);  
       ggg->add(btna, 20);  

       treeRoot = move(ggg);  
   }  
};  