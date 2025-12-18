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
#include "ProgressBar.h"
#include <StaticList.h>
#include "ProportionalSpacedList.h"

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
        label->setColour(Color::Yellow)
            .setTextJustification(TextJustification::CENTER)
            .setTextColour(Color::Green);

        

        TextButtonPtr hideFirstLabelButton = TextButton("Hide First Label");
        hideFirstLabelButton->onClickLeftDown([labelPtr = label.get()]() {
            if (labelPtr->isVisible()) {
                labelPtr->setIsVisibleFalse();
            }
            else {
                labelPtr->setIsVisibleTrue();
            }
            });
		verticalScroll->add(move(hideFirstLabelButton));
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
           .setPressedColour(Color::Blue)
           ;

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
       ui->addKeyPressLambda([k = labelledCheckBox.get()]() {
           k->checkBox->toggle(false);
           }, static_cast<uint32_t>(Keyboard::Key::C));
	   verticalScroll->add(move(labelledCheckBox));
       

	   TextButtonPtr addButtonButton = TextButton("Add Button");
       addButtonButton->onClickLeftDown(addTreeNode)
           .setColour(Color::Yellow)
           .setHoverColour(Color(232, 126, 5))
           .setPressedColour(Color::Green) // Set the pressed colour for the button   
		   .setTextJustification(TextJustification::CENTER)
		   .setTextColour(Color::Blue);
	   verticalScroll->add(move(addButtonButton));

	   TextButtonPtr keyPressButton = TextButton("Add enterKey pring");

       keyPressButton->onClickLeftDown([ui, button = keyPressButton.get()]() {
           function<void()> printEnter = []() { cout << "Enter Key Pressed" << endl; };
           static uint32_t enterPrintLambdaID = -1;
           if (enterPrintLambdaID == -1)
           {
               enterPrintLambdaID = ui->addKeyPressLambda(printEnter, static_cast<uint32_t>(Keyboard::Key::Enter));
           }
           else
           {
               ui->removeKeyPressLambda(enterPrintLambdaID, static_cast<uint32_t>(Keyboard::Key::Enter));
               enterPrintLambdaID = -1;
           }
           })
           .setColour(Color::Yellow)
           .setHoverColour(Color(232, 126, 5))
           .setPressedColour(Color::Green); // Set the pressed colour for the button
       
       verticalScroll->add(move(keyPressButton));

       TextButtonPtr r = TextButton("ListLayoutDemo");
           r->setColour(Color::Blue)
           .setPressedColour(Color::Blue)
		   .onClickLeftDown(makeSwitchPageLambda(PageTypes::LIST_LAYOUT_DEMO));
        
	   verticalScroll->add(move(r));

	   TextButtonPtr f = TextButton("Text Justification Demo");
       f->setColour(Color(33, 33, 33))
		   .onClickLeftDown(makeSwitchPageLambda(PageTypes::TEXT_JUSTIFICATION_PAGE));
	   verticalScroll->add(move(f));


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

	   ScrollPtr scroll = Scroll();
       scroll->setBackgroundColour(Color::Green);

       EvenListPtr vert2 = EvenList();
	   vert2->setMargin(4); // Set the margin between elements in the vertical scroll area

	   LabelPtr label2 = Label("label in scroll area");
	   vert2->add(move(label2));

	   TextBoxPtr textBoxInScroll = TextBox("TextBox in Scroll Area");
	   vert2->add(move(textBoxInScroll));

	   int vert2Height = 0; // Initialize the height of the vertical scroll area
       for (int t = 0; t < 20; t++) {
           ColouredButton btnb(Color::Blue);
           btnb.onClick(makeChangeColourLambda(btnb.getRootNodePointer()));
           vert2->add(btnb); // Add btnb to the scroll area
		   vert2Height += 40; // Increment the height for each button added
       }
	   vert2->setSize(Vector2f(200, vert2Height)); // Set the size of the vertical scroll area based on the number of buttons
	   scroll->setLayout(move(vert2)); // Add the vertical scroll to the scroll area



	   StaticListPtr s = StaticList();
       s->setHorizontal();
       ColouredButton btny(Color::Blue);
       btny.onClick(makeChangeColourLambda(btny.getRootNodePointer()));
       btny.setSize(Vector2f(30, 20));
	   s->add(btny);

       ColouredButton btny1(Color::Blue);
       btny1.onClick(makeChangeColourLambda(btny1.getRootNodePointer()));
       btny1.setSize(Vector2f(40, 30));
       s->add(btny1);

       ColouredButton btny2(Color::Blue);
       btny2.onClick(makeChangeColourLambda(btny2.getRootNodePointer()));
       btny2.setSize(Vector2f(20, 40));
       s->add(btny2);

       ColouredButton btny3(Color::Blue);
       btny3.onClick(makeChangeColourLambda(btny3.getRootNodePointer()));
       btny3.setSize(Vector2f(60, 50));
       s->add(btny3);

       vert->add(move(s)); // Add btny to the vertical scroll
	   vert->add(move(scroll)); // Add the scroll area to the vertical scroll
	   vert->setBackgroundColour(Color(100, 0, 100));
	   
       ProportionalSpacedListPtr mainLayour = ProportionalSpacedList();
       //progress bar
	   ProgressBarPtr progressBar = ProgressBar();
	   progressBar->setBackgroundColour(Color(0, 0, 100))
		   .setBarColour(Color::Green)
		   .setProgress(0.0f);
	   ProportionalSpacedListPtr progressBarLayout = ProportionalSpacedList();
	   progressBarLayout->setMargin(2)
           .setHorizontal()
           .setBackgroundColour(Color::Cyan);
	   TextButtonPtr increaseProgressButton = TextButton("Inc Prog");
       increaseProgressButton->onClickLeftDown([pBar = progressBar.get()]() {
		   pBar->setProgress(pBar->getProgress() + 0.06f);
           });
	   TextButtonPtr decreaseProgressButton = TextButton("Dec Prog");
	   decreaseProgressButton->onClickLeftDown([pBar = progressBar.get()]() {
		   pBar->setProgress(pBar->getProgress() - 0.06f);
		   });
       progressBarLayout->add(move(progressBar), 80);
       progressBarLayout->add(move(decreaseProgressButton), 10);
       progressBarLayout->add(move(increaseProgressButton), 10);

	   mainLayour->add(move(progressBarLayout), 7);
       HorizontalSplitterPtr horizontalSplitter = HorizontalSplitter(ui->getOrigin(), ui->getSize());
       horizontalSplitter->add(move(vert), 30);  
       horizontalSplitter->add(move(verticalScroll), 50);  
       horizontalSplitter->add(btna, 20);  
	   mainLayour->add(move(horizontalSplitter), 90);

       treeRoot = move(mainLayour);  
   }  
};  