#ifndef LINE_CHART_H
#define LINE_CHART_H

#include "UI_DLL_Interface.h"
#include "memory"
#include "Branch.h"

namespace internal {
	class UI_API LineChart : public Branch {
	public:
		LineChart();
		~LineChart() = default;
		void calcPositions() override;
		void preDraw() override;

	private:
		VertexArray lineVertices;
		Color lineColour = Color::Red;
		Color backgroundColour = Color::Black;
		int margin = 70;
		int pixelsBetweenNumbers = 60;
	};

}

using LineChartPtr = std::unique_ptr<class internal::LineChart>;

LineChartPtr UI_API LineChart();

#endif