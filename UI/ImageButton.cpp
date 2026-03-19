#include "pch.h"
#include "ImageButton.h"

internal::ImageButton::ImageButton(string imagePath) : InteractiveFluent<ImageButton, Branch>()
{
	// Load the texture from the specified image path
	if (!imageTexture.loadFromFile(imagePath)) {
		throw std::runtime_error("Failed to load image: " + imagePath);
	}
	setPreDrawNeededTrue();
}

void internal::ImageButton::preDraw()
{
	Branch::preDraw();
	Sprite sprite(imageTexture);
	sprite.setPosition(origin);
	sprite.setScale(Vector2f(size.x / imageTexture.getSize().x, size.y / imageTexture.getSize().y));
	screenTexture->draw(sprite);
}

ImageButtonPtr ImageButton(string imagePath) {
	return make_unique<internal::ImageButton>(imagePath);
}