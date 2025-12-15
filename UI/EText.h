
#ifndef ETEXT_H
#define ETEXT_H

#include "UI_DLL_Interface.h"

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>


using namespace sf;
using namespace std;
class Branch;

enum class TextJustification {
	LEFT,
	CENTER,
	RIGHT
};

class UI_API EText {
private:
	/** SFML Text object that handles the rendering of the text */
	Text textSfml;
	/** The text content */
	string text;
	TextJustification justification = TextJustification::LEFT;
public:
	static RenderTexture* screenTexture;
	static RenderWindow* window;
	/** For drawing the text and the cursor to. This texture is then rendered to the screen texture */
	//the cached texture is as big as its container sets it to. text justification is done via moving the text object inside the cached texture
	RenderTexture cachedTexture;
	Vector2f windowPosition;//position of the text box in the window
	Vector2f windowSize;//size of the text box in the window
	sf::Clock clock;
	float elapsedTime = 0.f;
	float oldCharIndex = 0;
	const int cursorWidth = 4;
	int currentCharIndex = -1;
	TextJustification getJustification() {
		return justification;
	}
	

	EText(Font& font, string initialText) : textSfml(font, initialText) {
		text = initialText;
		textSfml.setFillColor(sf::Color::Magenta);
		textSfml.setPosition(Vector2f(0, 0));
		textSfml.setCharacterSize(20);
		textSfml.setStyle(sf::Text::Bold);

	}

	bool draw();
	/**
	* 
	*/

	void Justify()
	{
		switch (justification)
		{
		case TextJustification::LEFT:
			textSfml.setOrigin(Vector2f(0, 0));
			break;
		case TextJustification::CENTER:
		{
			sf::FloatRect bounds = textSfml.getLocalBounds();
			float widthEeitherSideOfText = (windowSize.x - bounds.size.x) / 2;

			textSfml.setOrigin(Vector2f(-widthEeitherSideOfText, 0));//I HAVE NO IDEA WHY MAKING IT NEGATIVE WORKS BUT IT DOES
			break;
		}
		case TextJustification::RIGHT:
		{
			FloatRect bounds = textSfml.getLocalBounds();
			float widthLeftOfText = windowSize.x - bounds.size.x;
			textSfml.setOrigin(Vector2f(-widthLeftOfText, 0));//I HAVE NO IDEA WHY MAKING IT NEGATIVE WORKS BUT IT DOES
			break;
		}
		default:
			break;
		}
	}

	void setPosition(Vector2f position)
	{
		position.x += 10;
		windowPosition = position;
		Justify();
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}

	void setTextJustification(TextJustification justification)
	{
		this->justification = justification;
		Justify();
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}

	void setSize(Vector2f size)
	{
		size.x -= 20;
		cachedTexture.resize({ static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y) });
		windowSize = size;
		Justify();
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}

	void setTextColour(Color c)
	{
		textSfml.setFillColor(c);
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}

	void setText(string newText)
	{
		//screenTexture->setActive(true);
// Save GL scissor state



		elapsedTime = 0;
		textSfml.setString(newText);
		Justify();
		cachedTexture.clear(Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();



		//FloatRect bounds = textSfml.getGlobalBounds();//CURSOR HAS TAKEN OVER THIS FUNCTIONALITYS ... WILL NOT WORK IF TEXT IS SET EXTERNALLY TO TYPING 
		//int textWidth = bounds.size.x;
		//if (textWidth > windowSize.x)
		//{
		////	textSfml.setPosition(Vector2f(windowSize.x - textWidth, 0));//COULD TRY SOME CLEVER WAY OF ONLY RENDERRING VISIBLE TEXT????????????????????????????????????????????
		//}
		//else if(textSfml.getPosition().x < 0)
		//{
		//	//textSfml.setPosition(Vector2f(0, 0));
		//}
		text = newText;


		/*
		WHEN TEXT REDRAWS, IT NEEDS TO REDRAW THE STUFF BEHIND IT BEFORE IT REDRAWS ITSELF


		IF REDRAW TEXT IS NEEDDED THEN THE WIDGET SHOULD REDRAW ITSELF AND THEN THE TEXT IT CONTAINS
		*/
	}
	string getText()
	{
		return text;
	}

	Vector2f getMinTextSize()
	{
		sf::FloatRect bounds = textSfml.getLocalBounds();
		bounds.size.x += 20;
		bounds.size.y += 10;
		return bounds.size;
	}
};


#endif