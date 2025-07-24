#include "Page.h"  
#include "ColouredButton.h"  
#include "TextButton.h"
#include "CallBack.h"  
#include "HorizontalProportionalSpacedBar.h"  
#include <memory>  
#include "PageSwitcher.h"
#include "Label.h"

class Page1 : public Page {  
private:

public:
    int page2ID;
    PageSwitcher& pageSwitcher; // Reference to the PageSwitcher to switch back to Page
    Page1(PageSwitcher& pageSwitcher, int page2ID) : pageSwitcher(pageSwitcher){
		this->page2ID = page2ID; // Store the Page2 ID for switching later  
    }
   void createTree() override  
   {  
       Vector2f buttonOrigin2 = Vector2f(90, 90);  
       Vector2f buttonSize2 = Vector2f(40, 30);  
       unique_ptr<TextBox> j = ui->addButton(buttonOrigin2, buttonSize2, "hello");  
       void* d = nullptr;
       unique_ptr<Callback> c = makeCallBack(incrementSize, d);
       ui->addOnClick(move(c), j->id);//WOUDL NEED TO MAKE A FOX  

       //create the scroll area  
       unique_ptr<VerticalScroll> verticalScroll = make_unique<VerticalScroll>(Vector2f(200, 400), Vector2f(200, 200));  

	   unique_ptr<Label> label = make_unique<Label>("first label", Vector2f(0, 0), Vector2f(200, 30));
	   verticalScroll->add(move(label));


	   TextButton TB("Add Button");
       TB.onClickLeftDown(move(makeCallBack(addTreeNode, verticalScroll.get())), *ui);
           TB.onClickLeftDown(move(makeCallBack(addTreeNode, verticalScroll.get())), *ui).setColour(Color::Yellow);
	   verticalScroll->add(TB);



       ColouredButton btn2 = ColouredButton(Color::Black);
       unique_ptr<Callback> c2 = makeCallBack(removeTreeNode, new std::tuple<Branch*, int>(verticalScroll.get(), btn2.getID()));
       btn2.onClick(move(c2), *ui);
       verticalScroll->add(btn2);  

       ColouredButton btn3 = ColouredButton(Color::Blue);
	   void* u = nullptr;
       unique_ptr<Callback> c3 = makeCallBack(switchToPage2, this);
       btn3.onClick(move(c3), *ui);
       verticalScroll->add(btn3);  //CANNOT MOVE IT TWICE

       ColouredButton btn4 = ColouredButton(Color::Magenta);
       unique_ptr<Callback> c4 = makeCallBack(changeColourBtn, btn4.getRootNodePointer());
       btn4.onClick(move(c4), *ui);  
       verticalScroll->add(btn4);  

       verticalScroll->add(move(j));  

       ColouredButton btn5 = ColouredButton(Color::Cyan);
       unique_ptr<Callback> c5 = makeCallBack(changeColourBtn, btn5.getRootNodePointer());
       btn5.onClick(move(c5), *ui);  
       verticalScroll->add(btn5);  

       unique_ptr<HorizontalProportionalSpacedBar>ggg = make_unique<HorizontalProportionalSpacedBar>(ui->getOrigin(), ui->getSize());  

       ColouredButton btna(Color::Blue);  
       unique_ptr<Callback> ca = makeCallBack(changeColourBtn, btna.getRootNodePointer());
       btna.onClick(move(ca), *ui);  

       ColouredButton btnb(Color::Blue);  
       unique_ptr<Callback> cb = makeCallBack(changeColourBtn, btnb.getRootNodePointer());
       btnb.onClick(move(cb), *ui);  

       ggg->add(btna, 20);  
       ggg->add(move(verticalScroll), 50);  
       ggg->add(btnb, 20);  

       treeRoot = move(ggg);  
   }  
   static void incrementSize(void* param) {  
       cout << "clicked 2" << endl;  
       //Button* b = (Button*)param;  
       //height += 10;  
       //width += 10;  
       //b->setSize(Vector2f(width, height));  
   }  

   static void addTreeNode(VerticalScroll* branch)  
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
       btn.onClick(makeCallBack(removeTreeNode, new tuple<Branch*, int>(branch, btn.getID())), *UI::ui);  
       branch->add(btn);  
   }  



   static void changeColorLabel(Label* label)
   {
       if (label->getColour() == Color::Yellow)
       {
           label->setColour(Color::Cyan);
       }
       else {
           label->setColour(Color::Yellow);
       }
   }

   static void changeColourBtn(ColouredBox* button)
   {  
       if (button->colour == Color::Blue)
       {  
           button->setColour(Color::Red);
       }  
       else {  
           button->setColour(Color::Blue);
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