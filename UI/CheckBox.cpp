#include "pch.h"
#include "CheckBox.h"
#include "UI.h"

CheckBoxPtr CheckBox()
{
	return make_unique<internal::CheckBox>();
}

internal::CheckBox::CheckBox()
{
	vertices = VertexArray(sf::PrimitiveType::Triangles, 24);//Needs more vertices for the tick
	//register the lambdas for checking and unchecking
	UI* ui = UI::getInstance();

	ui->addLeftDown([this]() {this->toggle(); }, this->id);
}

void internal::CheckBox::setChecked(bool c)
{
	const int borderThickness = 2;
	if (c)
	{
		check(Vector2f(origin.x + borderThickness, origin.y + borderThickness), Vector2f(antiOrigin.x - borderThickness, antiOrigin.y - borderThickness));
	}
	else
	{
		unCheck();
	}
	notifyRedrawNeeded();
}

void internal::CheckBox::toggle()
{
	const int borderThickness = 2;
	if (checked)
	{
		unCheck();
	}
	else
	{
		check(Vector2f(origin.x + borderThickness, origin.y + borderThickness), Vector2f(antiOrigin.x - borderThickness, antiOrigin.y - borderThickness));
	}
	notifyRedrawNeeded();
}

inline void squareDrawnArea(Vector2f& origin, Vector2f& antiOrigin)
{
	if (antiOrigin.x - origin.x > antiOrigin.y - origin.y)
	{
		int height = antiOrigin.y - origin.y;
		origin.x = origin.x + ((antiOrigin.x - origin.x) - height) / 2;
		antiOrigin.x = origin.x + height;
	}
	else if (antiOrigin.y - origin.y > antiOrigin.x - origin.x)
	{
		int width = antiOrigin.x - origin.x;
		origin.y = origin.y + ((antiOrigin.y - origin.y) - width) / 2;
		antiOrigin.y = origin.y + width;
	}
}

void internal::CheckBox::onToggle(std::function<void()> g)
{
	UI* ui = UI::getInstance();
	ui->addLeftDown(g, this->id);
}

void internal::CheckBox::updateVerticesPosition()
{
	Vector2f drawnOrigin = origin;
	Vector2f drawnAntiOrigin = antiOrigin;
	squareDrawnArea(drawnOrigin, drawnAntiOrigin);
	const int borderThickness = 2;
	//make the biggest quad which is the boarder
	//first triangle
	vertices[0].position = drawnOrigin;
	vertices[1].position = Vector2f(drawnOrigin.x, drawnAntiOrigin.y);
	vertices[2].position = Vector2f(drawnAntiOrigin.x, drawnOrigin.y);
	//second triangle
	vertices[3].position = Vector2f(drawnAntiOrigin.x, drawnOrigin.y);
	vertices[4].position = Vector2f(drawnOrigin.x, drawnAntiOrigin.y);
	vertices[5].position = Vector2f(drawnAntiOrigin.x, drawnAntiOrigin.y);

	for (int i = 0; i < 6; i++)
	{
		vertices[i].color = Color::Blue;
	}
	//make the smaller quad which is the background colour
	//first triangle
	vertices[6].position = Vector2f(drawnOrigin.x + borderThickness, drawnOrigin.y + borderThickness);
	vertices[7].position = Vector2f(drawnOrigin.x + borderThickness, drawnAntiOrigin.y - borderThickness);
	vertices[8].position = Vector2f(drawnAntiOrigin.x - borderThickness, drawnOrigin.y + borderThickness);
	//second triangle
	vertices[9].position = Vector2f(drawnAntiOrigin.x - borderThickness, drawnOrigin.y + borderThickness);
	vertices[10].position = Vector2f(drawnOrigin.x + borderThickness, drawnAntiOrigin.y - borderThickness);
	vertices[11].position = Vector2f(drawnAntiOrigin.x - borderThickness, drawnAntiOrigin.y - borderThickness);
	for (int i = 6; i < 12; i++)
	{
		vertices[i].color = Color::Red;
	}
	if (checked)
	{
		check(Vector2f(origin.x + borderThickness, origin.y + borderThickness), Vector2f(antiOrigin.x - borderThickness, antiOrigin.y - borderThickness));
	}
}

void internal::CheckBox::unCheck()
{
	checked = false;
	//set the tick vertices to 0,0
	for (int i = 12; i < 24; i++)
	{
		vertices[i].position = Vector2f(0, 0);
	}
}

void internal::CheckBox::check(Vector2f origin, Vector2f antiOrigin)//might not need to pass these in
{
	Vector2f drawnOrigin = origin;
	Vector2f drawnAntiOrigin = antiOrigin;
	squareDrawnArea(drawnOrigin, drawnAntiOrigin);
	//modify the drawn points so that it is always a square
	checked = true;
	//draw the tick
	int boxWidth = drawnAntiOrigin.x - drawnOrigin.x;
	const int tickThickness = boxWidth / 5;
	const int tickMargin = 2;
	const float startProp = 0.666;//the tick will start at 66.6% of the way down the box
	const float bottomProp = 0.25;//the bottom of the tick will be at 25% of the way accross the bottom

	int tickWidth = drawnAntiOrigin.x - drawnOrigin.x - (2 * tickMargin);
	int tickHeight = drawnAntiOrigin.y - drawnOrigin.y - (2 * tickMargin);

	//draw first quad

	int leftSideTouch = drawnOrigin.y + tickMargin + (tickHeight * startProp);

	int leftX = drawnOrigin.x + tickMargin;
	int rightX = drawnOrigin.x + tickMargin + (tickWidth * bottomProp);

	int rightBottomY = drawnAntiOrigin.y - tickMargin;
	int rightTopY = drawnAntiOrigin.y - tickMargin - tickThickness;

	int leftBottomY = leftSideTouch + (tickThickness / 2);
	int leftTopY = leftSideTouch - (tickThickness / 2);
	//first triangle
	vertices[12].position = Vector2f(leftX, leftTopY);
	vertices[13].position = Vector2f(rightX, rightBottomY);
	vertices[14].position = Vector2f(leftX, leftBottomY);
	vertices[12].color = Color::Blue;
	vertices[13].color = Color::Blue;
	vertices[14].color = Color::Blue;
	//second triangle
	vertices[15].position = Vector2f(leftX, leftTopY);
	vertices[16].position = Vector2f(rightX, rightTopY);
	vertices[17].position = Vector2f(rightX, rightBottomY);
	vertices[15].color = Color::Cyan;
	vertices[16].color = Color::Cyan;
	vertices[17].color = Color::Cyan;

	//draw second quad

	leftX = rightX;
	int middleRightX = drawnAntiOrigin.x - tickMargin - tickThickness;
	int rightRightX = drawnAntiOrigin.x - tickMargin;

	leftTopY = rightTopY;
	leftBottomY = rightBottomY;

	int topY = drawnOrigin.y + tickMargin;

	//first triangle
	vertices[18].position = Vector2f(leftX, leftTopY);
	vertices[19].position = Vector2f(middleRightX, topY);
	vertices[20].position = Vector2f(rightRightX, topY);
	vertices[18].color = Color::Blue;
	vertices[19].color = Color::Blue;
	vertices[20].color = Color::Blue;
	//second triangle
	vertices[21].position = Vector2f(leftX, leftBottomY);
	vertices[22].position = Vector2f(leftX, leftTopY);
	vertices[23].position = Vector2f(rightRightX, topY);
	vertices[21].color = Color::Cyan;
	vertices[22].color = Color::Cyan;
	vertices[23].color = Color::Cyan;
}