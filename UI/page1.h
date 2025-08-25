#include "Page.h"  
#include "ColouredButton.h"  
#include "TextButton.h"
#include "CallBack.h"  
#include "HorizontalProportionalSpacedBar.h"  
#include <memory>  
#include "PageSwitcher.h"
#include "Label.h"
#include "Vertical.h"
#include "Scroll.h"



class Page1 : public Page {  
private:
   // LabelColour TBpressedColour;
	//LabelColour TBreleasedColour; // Store the label and its colour for later use
    TextButtonMaker TB = TextButtonMaker();
public:
    int page2ID;
    PageSwitcher& pageSwitcher; // Reference to the PageSwitcher to switch back to Page
	Page1(Page1&& other) = default; // Move constructor for Page1
    Page1(PageSwitcher& pageSwitcher, int page2ID) : pageSwitcher(pageSwitcher){
		this->page2ID = page2ID; // Store the Page2 ID for switching later  
    }
   void createTree() override  
   {   
	   UI* ui = UI::getInstance();
       unique_ptr<TextBox> j = ui->addButton("hello");  
       void* d = nullptr;
       unique_ptr<CallBack> c = makeCallBack(incrementSize, d);
       ui->addOnClick(move(c), j->id);//WOUDL NEED TO MAKE A FOX  

       //create the scroll area  
	   VerticalPtr verticalScroll = Vertical();
	   verticalScroll->setMargin(4); // Set the margin between elements in the scroll area
       verticalScroll->setBackgroundColour(Color(63, 3, 153)); // Set the background colour of the scroll area

	   unique_ptr<Label> label = make_unique<Label>("first label", Vector2f(0, 0), Vector2f(200, 30));
	   verticalScroll->add(move(label));

       TB.createButton("Add Button")
           .onClickLeftDown(move(makeCallBack(addTreeNode, verticalScroll.get())))
		   .setPressedColour(Color::Green) // Set the pressed colour for the button
           .setColour(Color::Yellow);      
	   verticalScroll->add(TB);



       ColouredButton btn2 = ColouredButton(Color::Black);
       CallBackPtr c2 = makeCallBack(removeTreeNode, new std::tuple<Branch*, int>(verticalScroll.get(), btn2.getID()));
       btn2.onClick(move(c2));
       verticalScroll->add(btn2);  

       ColouredButton btn3 = ColouredButton(Color::Blue);
	   void* u = nullptr;
       CallBackPtr c3 = makeCallBack(switchToPage2, this);
       btn3.onClick(move(c3));
       verticalScroll->add(btn3);  //CANNOT MOVE IT TWICE

       ColouredButton btn4 = ColouredButton(Color::Magenta);
       CallBackPtr c4 = makeCallBack(changeColourBtn, btn4.getRootNodePointer());
       btn4.onClick(move(c4));  
       verticalScroll->add(btn4);  

       verticalScroll->add(move(j));  

       ColouredButton btn5 = ColouredButton(Color::Cyan);
       CallBackPtr c5 = makeCallBack(changeColourBtn, btn5.getRootNodePointer());
       btn5.onClick(move(c5));  
       verticalScroll->add(btn5);  

       unique_ptr<HorizontalProportionalSpacedBar>ggg = make_unique<HorizontalProportionalSpacedBar>(ui->getOrigin(), ui->getSize());  

       ColouredButton btna(Color::Blue);  
       CallBackPtr ca = makeCallBack(changeColourBtn, btna.getRootNodePointer());
       btna.onClick(move(ca));  

       VerticalPtr vert = Vertical();//make_unique<Vertical>(Vector2f(0, 0), Vector2f(200, 200));

	   unique_ptr<Scroll> scroll = make_unique<Scroll>();
       scroll->setBackgroundColour(Color::Green);

       VerticalPtr vert2 = Vertical();
	   vert2->setMargin(4); // Set the margin between elements in the vertical scroll area


	   int vert2Height = 0; // Initialize the height of the vertical scroll area
       for (int t = 0; t < 20; t++) {
           ColouredButton btnb(Color::Blue);
           CallBackPtr cb = makeCallBack(changeColourBtn, btnb.getRootNodePointer());
           btnb.onClick(move(cb));
           vert2->add(btnb); // Add btnb to the scroll area
		   vert2Height += 40; // Increment the height for each button added
       }
	   vert2->setSize(Vector2f(200, vert2Height)); // Set the size of the vertical scroll area based on the number of buttons
	   scroll->add(move(vert2)); // Add the vertical scroll to the scroll area
       ColouredButton btny(Color::Blue);
       CallBackPtr cy = makeCallBack(changeColourBtn, btny.getRootNodePointer());
       btny.onClick(move(cy));
       ui->addMouseWheelCallback(move(makeScrollCallBack(printText, scroll.get())), scroll->id); // Add mouse wheel callback to the scroll area

       vert->add(btny); // Add btny to the vertical scroll
	   vert->add(move(scroll)); // Add the scroll area to the vertical scroll
	   


       ggg->add(move(vert), 30);  
       ggg->add(move(verticalScroll), 50);  
       ggg->add(btna, 20);  

       treeRoot = move(ggg);  
   }  
   static void incrementSize(void* param) {  
       cout << "clicked 2" << endl;  
       //Button* b = (Button*)param;  
       //height += 10;  
       //width += 10;  
       //b->setSize(Vector2f(width, height));  
   }  

   static void printText(tuple<Scroll*, int> param) {
       
	   cout << "clicked" << endl;
	   cout << "delta: " << get<1>(param) << endl;
	   Scroll* scroll = get<0>(param);
	   scroll->incrementOffset(get<1>(param)); // Increment the scroll offset by the delta value
   }

   static void addTreeNode(class _Vertical* branch)  
   {  
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
       btn.onClick(makeCallBack(removeTreeNode, new tuple<Branch*, int>(branch, btn.getID())));
       branch->add(btn);  
   }  





   static void changeColourBtn(ColouredBox* button)
   {  
       if (button->colour == Color::Cyan)
       {  
           button->setColour(Color::Magenta);
       }  
       else {  
           button->setColour(Color::Cyan);
       }  
   }  

   static void removeTreeNode(tuple<Branch*, int>* tuple)  
   {  
       Branch* branch = get<0>(*tuple);  
       int id = get<1>(*tuple);  
       branch->remove(id);  
       delete tuple;//Clean up the dynamically allocated memory  
   }  

   static void switchToPage2(Page1* page1) {
       page1->pageSwitcher.showPage(page1->page2ID);
   }

};  