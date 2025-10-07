
#ifndef ETEXT_H
#define ETEXT_H
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "UI_DLL_Interface.h"
using namespace sf;
using namespace std;

class UI_API EText {
private:
	/** SFML Text object that handles the rendering of the text */
	Text textSfml;
	/** The text content */
	string text;
public:
	static RenderTexture* screenTexture;
	static RenderWindow* window;
	/** For drawing the text and the cursor to. This texture is then rendered to the screen texture */
	RenderTexture cachedTexture;
	Vector2f windowPosition;
	Vector2f windowSize;
	sf::Clock clock;
	float elapsedTime = 0.f;
	float oldCharIndex = 0;
	const int cursorWidth = 4;
	int currentCharIndex = -1;

	EText(Font& font, string initialText) : textSfml(font, initialText) {
		text = initialText;
		textSfml.setFillColor(sf::Color::Red);
		textSfml.setPosition(Vector2f(0, 0));

	}

	bool draw()
	{
		if (currentCharIndex != oldCharIndex && currentCharIndex != -1)//if the user has used the arrow keys to move in the string
		{
			elapsedTime = 0;//make sure that the cursor is drawn
			oldCharIndex = currentCharIndex;
			cachedTexture.clear(Color::Transparent);
			cachedTexture.draw(textSfml);
			cachedTexture.display();
		}


		if (currentCharIndex != -1)
		{
			elapsedTime += clock.restart().asSeconds();
			if (elapsedTime < 0.25) {
				Vector2f cursorPosition = textSfml.findCharacterPos(currentCharIndex);
				RectangleShape cursor;//rect is the cursor
				//redraw text so that the old curser line is removed
				cachedTexture.clear(Color::Transparent);
				cachedTexture.draw(textSfml);

				cursorPosition.y += 1;//get it pixel perfect

				cursor.setPosition(cursorPosition);

				//handle moving the SFML Text object position to keep the cursor within the bounds of the cached texture
				Vector2f textPosition = textSfml.getPosition();
				int cursorHeight = textSfml.getFont().getLineSpacing(textSfml.getCharacterSize());
				if (cursorPosition.x < 0)//if the cursor is to the left of the cachedTexture
				{
					
					textPosition.x -= (cursorPosition.x - 10);
					cursorPosition.x = 10;
				}
				else if (cursorPosition.x > cachedTexture.getSize().x)//if the cursor is to the right of the cachedTexture
				{
					textPosition.x -= (cursorPosition.x - cachedTexture.getSize().x) + cursorWidth;
					cursorPosition.x = cachedTexture.getSize().x - cursorWidth;
				}
				if (cursorPosition.y < 0)//if the cursor is above the cachedTexture
				{
					textPosition.y -= cursorPosition.y;
					cursorPosition.y = 0;
				}
				else if (cursorPosition.y + cursorHeight > cachedTexture.getSize().y)//if the cursor is below the cachedTexture
				{
					textPosition.y -= (cursorPosition.y - cachedTexture.getSize().y) + cursorHeight + 10;
					cursorPosition.y = cachedTexture.getSize().y + cursorHeight + 10;
				}
				if (textPosition != textSfml.getPosition())//if the text position has changed, redraw the text
				{
					textSfml.setPosition(textPosition);
				}

				unsigned int k = textSfml.getCharacterSize();
				cursor.setSize(Vector2f(cursorWidth, textSfml.getFont().getLineSpacing(k)));
				cursor.setFillColor(Color::Magenta);
				cachedTexture.draw(cursor);


				cachedTexture.display();
			}
			else if (elapsedTime < 0.5)
			{
				cachedTexture.clear(Color::Transparent);
				cachedTexture.draw(textSfml);
				cachedTexture.display();

			}
			else {
				elapsedTime = 0;
			}

		}


		sf::Sprite sprite(cachedTexture.getTexture());
		sprite.setPosition(windowPosition);

		RenderTexture j = RenderTexture(cachedTexture.getSize());
		j.clear(Color::Cyan);

		Sprite G = Sprite(j.getTexture());
		G.setPosition(windowPosition);

		//	screenTexture->draw(G);//THIS PROOVES THAT THE PROBLEM WITH THE TEXTBOX IS BECAUSE THE SCREEN ISNT BEING CLEARED PROPERLY

		screenTexture->draw(sprite);//THIS IS BEING HIT FOREVER WHICH SHOULD NOT BE HAPPENING

		return false;
	}
	/**
	* 
	*/
	void setPosition(Vector2f position)
	{
		position.x += 10;
		windowPosition = position;
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}
	void setSize(Vector2f size)
	{
		size.x -= 20;
		cachedTexture.resize({ static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y) });
		windowSize = size;
		cachedTexture.clear(sf::Color::Transparent);
		cachedTexture.draw(textSfml);
		cachedTexture.display();
	}
	void setText(string newText)
	{
		elapsedTime = 0;
		textSfml.setString(newText);
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
};


#endif