#include "Page.h"  
#include "ColouredButton.h"  
#include "TextButton.h"
#include "HorizontalSplitter.h"
#include <memory>  
#include "PageSwitcher.h"
#include "Label.h"
#include "EvenList.h"
#include "Scroll.h"
#include "PageTypes.h"
#include <functional>
#include "CheckBox.h"
#include "LabelledCheckBox.h"


class Page1 : public Page {  
private:
	
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
       EvenListPtr verticalScroll = EvenList();
	   verticalScroll->setMargin(4); // Set the margin between elements in the scroll area       
       verticalScroll->setBackgroundColour(Color(63, 3, 153)); // Set the background colour of the scroll area
       //verticalScroll->setHorizontal();

	   LabelPtr label = Label("first label");
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

       function<void()> printToggle = []() {
           cout << "toggled" << endl;
           };
       checkBox->onToggle(printToggle);

	   TextButtonPtr isCheckedButton = TextButton("Is Checked?");

       isCheckedButton->onClickLeftDown([checkBoxPtr = checkBox.get()]() {
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
	   verticalScroll->add(move(isCheckedButton));

	   LabelledCheckBoxPtr labelledCheckBox = LabelledCheckBox("Labelled CheckBox");
       labelledCheckBox->checkBox->onToggle([lab = labelledCheckBox.get()]() {
           if (lab->checkBox->checked) {
               lab->label->setText("Checked");
           }
           else {
               lab->label->setText("Not Checked");
           }
           });
	   verticalScroll->add(move(labelledCheckBox));

	   TextButtonPtr addButtonButton = TextButton("Add Button");
       addButtonButton->onClickLeftDown(addTreeNode)
           .setColour(Color::Yellow)
           .setPressedColour(Color::Green); // Set the pressed colour for the button    
	   verticalScroll->add(move(addButtonButton));

       TextButtonPtr r = TextButton("ListLayoutDemo");
           r->setColour(Color::Blue)
           .setPressedColour(Color::Blue)
		   .onClickLeftDown(makeSwitchPageLambda(PageTypes::LIST_LAYOUT_DEMO));
        
	   verticalScroll->add(move(r));



       ColouredButton btn2 = ColouredButton(Color::Black);
	   function<void()> removeTreeNode = [verticalScrollPtr = verticalScroll.get(), btnID = btn2.getID()]() {
		   verticalScrollPtr->remove(btnID);
		   };
	   btn2.onClick(removeTreeNode);

       verticalScroll->add(btn2);  

       TextButtonPtr page2Button = TextButton("Page 2");
       page2Button->setColour(Color::Cyan)
		   .setPressedColour(Color::Magenta)
		   .onClickLeftDown(makeSwitchPageLambda(PageTypes::PAGE_2));
       verticalScroll->add(move(page2Button));

       TextButtonPtr page3Button = TextButton("Page 3");
       page3Button->setColour(Color::Cyan)
		   .setPressedColour(Color::Magenta)
		   .onClickLeftUp(makeSwitchPageLambda(PageTypes::PAGE_3), true);
	   verticalScroll->add(move(page3Button));  

       ColouredButton btn4 = ColouredButton(Color::Magenta);

	   
	   btn4.onClick(makeChangeColourLambda(btn4.getRootNodePointer()));

       verticalScroll->add(btn4);  

       verticalScroll->add(move(j));  

       ColouredButton btn5 = ColouredButton(Color::Cyan);
       btn5.onClick(makeChangeColourLambda(btn5.getRootNodePointer()));  



       verticalScroll->add(btn5);  

         

       ColouredButton btna(Color::Blue);  
       btna.onClick(makeChangeColourLambda(btna.getRootNodePointer()));

       EvenListPtr vert = EvenList();//make_unique<Vertical>(Vector2f(0, 0), Vector2f(200, 200));
	   vert->setChildSize(-1); // Let the EvenList calculate child size based on its own size

	   unique_ptr<Scroll> scroll = make_unique<Scroll>();
       scroll->setBackgroundColour(Color::Green);

       EvenListPtr vert2 = EvenList();
	   vert2->setMargin(4); // Set the margin between elements in the vertical scroll area


	   int vert2Height = 0; // Initialize the height of the vertical scroll area
       for (int t = 0; t < 20; t++) {
           ColouredButton btnb(Color::Blue);
           btnb.onClick(makeChangeColourLambda(btnb.getRootNodePointer()));
           vert2->add(btnb); // Add btnb to the scroll area
		   vert2Height += 40; // Increment the height for each button added
       }
	   vert2->setSize(Vector2f(200, vert2Height)); // Set the size of the vertical scroll area based on the number of buttons
	   scroll->setLayout(move(vert2)); // Add the vertical scroll to the scroll area
       ColouredButton btny(Color::Blue);
       btny.onClick(makeChangeColourLambda(btny.getRootNodePointer()));


	   //add mouseWheel lambda to scroll area
       function<void(int)> scroller = [scrollPtr = scroll.get()](int delta) {
           scrollPtr->incrementOffset(delta);
           };
	   ui->addMouseWheelLambda(scroller, scroll->id);

       vert->add(btny); // Add btny to the vertical scroll
	   vert->add(move(scroll)); // Add the scroll area to the vertical scroll
	   
       HorizontalSplitterPtr ggg = HorizontalSplitter(ui->getOrigin(), ui->getSize());

       ggg->add(move(vert), 30);  
       ggg->add(move(verticalScroll), 50);  
       ggg->add(btna, 20);  

       treeRoot = move(ggg);  
   }  
};  