#include "pch.h"
#include "ProgressBar.h"

internal::ProgressBar::ProgressBar()
{
	vertices = sf::VertexArray(sf::PrimitiveType::Triangles, 12);//check that leaf constructor isn't overwriting this
}

internal::ProgressBar& internal::ProgressBar::setBackgroundColour(Color c)
{
	// Set the colour of the background vertices (first 6 vertices)
	for (size_t i = 0; i < 6; ++i) {
		vertices[i].color = c;
	}
	notifyRedrawNeeded();
	return *this;
}

internal::ProgressBar& internal::ProgressBar::setBarColour(Color c)
{
	// Set the colour of the bar vertices (last 6 vertices)
	for (size_t i = 6; i < 12; ++i) {
		vertices[i].color = c;
	}
	notifyRedrawNeeded();
	return *this;
}

internal::ProgressBar& internal::ProgressBar::setProgress(float progress)
{
	if (progress < 0.0f)
	{
		progress = 0.0f;
	}
	if (progress > 1.0f)
	{
		progress = 1.0f;
	}
	this->progress = progress;
	float barWidth = size.x * progress;
	// First triangle of the bar
	vertices[6].position = origin;
	vertices[7].position = Vector2f(origin.x, antiOrigin.y);
	vertices[8].position = Vector2f(origin.x + barWidth, origin.y);
	// Second triangle of the bar
	vertices[9].position = Vector2f(origin.x + barWidth, origin.y);
	vertices[10].position = Vector2f(origin.x, antiOrigin.y);
	vertices[11].position = Vector2f(origin.x + barWidth, antiOrigin.y);
	notifyRedrawNeeded();
	return *this;
}

float internal::ProgressBar::getProgress()
{
	return progress;
}

ProgressBarPtr ProgressBar()
{
	return make_unique<internal::ProgressBar>();
}