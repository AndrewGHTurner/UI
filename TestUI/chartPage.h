#ifndef CHART_PAGE_H
#define CHART_PAGE_H

#include "Page.h"
#include <PageSwitcher.h>
#include "ProportionalSpacedList.h"
#include <TextButton.h>
#include <PageTypes.h>
#include "LineChart.h"

class ChartPage : public Page {

public:
	ChartPage(PageSwitcher& pageSwitcher) : pageSwitcher(pageSwitcher) {

	}
	void createTree() override
	{
		ProportionalSpacedListPtr mainContainer = ProportionalSpacedList();
		TextButtonPtr homeButton = TextButton("Home");
		homeButton->onClickLeftDown([this](EventData d) {
			this->pageSwitcher.showPage(PageTypes::PAGE_1);
			});
		mainContainer->add(move(homeButton), 10);

		LineChartPtr lineChart = LineChart();

		mainContainer->add(move(lineChart), 90);


		treeRoot = move(mainContainer);
	}
private:
	PageSwitcher& pageSwitcher;

};

#endif