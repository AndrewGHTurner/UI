#include "pch.h"
#include "LineChart.h"
#include "Label.h"

LineChartPtr LineChart() {
	return std::make_unique<internal::LineChart>();
}

internal::LineChart::LineChart() : Branch() {
	internal::LineChart::lineVertices = VertexArray(sf::PrimitiveType::LineStrip, 3);
	setPreDrawNeededTrue();

	LabelPtr title = ::Label("title");
	title->setColour(backgroundColour);
	title->setTextJustification(TextJustification::CENTER);
	children.push_back(move(title));//title is the first child in the children array
}

void internal::LineChart::calcPositions() {
	//set the positions of the axis lines
	lineVertices[0].position = Vector2f(origin.x + margin, origin.y + margin);//top left
	lineVertices[1].position = Vector2f(origin.x + margin, origin.y - margin + getSize().y);//bottom left
	lineVertices[2].position = Vector2f(origin.x + getSize().x - margin, origin.y - margin + getSize().y);//bottom right
	//set the colour
	lineVertices[0].color = lineColour;
	lineVertices[1].color = lineColour;
	lineVertices[2].color = lineColour;
	//set position of the title
	Label* title = static_cast<Label*>(children[0].get());
	title->setSize(Vector2f(getSize().x / 2, margin - 5));
	title->setOrigin(Vector2f(origin.x + getSize().x / 2 - title->getSize().x / 2, origin.y + 5));
	//for each subsequent label child set the position and text to be the axis numbers. Add new labels if needed
	int childIndex = 1;
	//x axis numbers first
	int x = pixelsBetweenNumbers;
	for (int xValue = getOrigin().x + margin + pixelsBetweenNumbers; xValue + pixelsBetweenNumbers < getOrigin().x + getSize().x; xValue += pixelsBetweenNumbers)
	{
		if (childIndex >= children.size())
		{
			LabelPtr newLabel = ::Label(std::to_string(xValue));
			newLabel->setColour(backgroundColour);
			newLabel->setTextJustification(TextJustification::CENTER);
			children.push_back(move(newLabel));
		}
		Label* label = static_cast<Label*>(children[childIndex].get());
		label->setText(std::to_string(x));
		label->setSize(Vector2f(pixelsBetweenNumbers, margin - 5));
		label->setOrigin(Vector2f(xValue - pixelsBetweenNumbers / 2, origin.y - margin + getSize().y + 5));
		childIndex++;
		x += pixelsBetweenNumbers;
	}
	//y axis numbers next
	int y = pixelsBetweenNumbers;
	for (int yValue = getOrigin().y + pixelsBetweenNumbers; yValue + pixelsBetweenNumbers < getOrigin().y + getSize().y - margin; yValue += pixelsBetweenNumbers)
	{
		if (childIndex >= children.size())
		{
			LabelPtr newLabel = ::Label(std::to_string(yValue));
			newLabel->setColour(backgroundColour);
			newLabel->setTextJustification(TextJustification::CENTER);
			children.push_back(move(newLabel));
		}
		Label* label = static_cast<Label*>(children[childIndex].get());
		label->setText(std::to_string(y));
		label->setSize(Vector2f(margin - 5, pixelsBetweenNumbers));
		label->setOrigin(Vector2f(origin.x + 4, yValue));
		childIndex++;
		y += pixelsBetweenNumbers;
	}
	//remove any extra labels that are not needed
	while (childIndex < children.size())
	{
		children.pop_back();
	}
}

void internal::LineChart::preDraw() {
	//draw the background
	VertexArray clearVertices(sf::PrimitiveType::Triangles, 6);
	//first triangle
	clearVertices[0].position = origin;
	clearVertices[1].position = Vector2f(origin.x, antiOrigin.y);
	clearVertices[2].position = Vector2f(antiOrigin.x, origin.y);
	//second triangle
	clearVertices[3].position = Vector2f(antiOrigin.x, origin.y);
	clearVertices[4].position = Vector2f(origin.x, antiOrigin.y);
	clearVertices[5].position = Vector2f(antiOrigin.x, antiOrigin.y);
	//set the colour
	clearVertices[0].color = backgroundColour;
	clearVertices[1].color = backgroundColour;
	clearVertices[2].color = backgroundColour;
	clearVertices[3].color = backgroundColour;
	clearVertices[4].color = backgroundColour;
	clearVertices[5].color = backgroundColour;
	screenTexture->draw(clearVertices);

	Branch::preDraw();
	RenderStates states;
	states.blendMode = sf::BlendAlpha;
	screenTexture->draw(lineVertices, states);
}