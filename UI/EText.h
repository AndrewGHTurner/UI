
#ifndef ETEXT_H
#define ETEXT_H
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;
using namespace std;

class EText {
private:
	Text textSfml;
	string text;
public:
	static RenderTexture* screenTexture;
	static RenderWindow* window;
	RenderTexture renderTexture;
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
			//	cout << currentCharIndex << endl;
				//cout << oldCharIndex << endl;
			elapsedTime = 0;//make sure that the cursor is drawn
			oldCharIndex = currentCharIndex;
			renderTexture.clear(Color::Transparent);
			renderTexture.draw(textSfml);
			renderTexture.display();
		}


		if (currentCharIndex != -1)
		{
			elapsedTime += clock.restart().asSeconds();
			if (elapsedTime < 0.25) {
				Vector2f cursorPosition = textSfml.findCharacterPos(currentCharIndex);
				RectangleShape rect;//rect is the cursor
				//redraw text so that the old curser line is removed
				renderTexture.clear(Color::Transparent);
				renderTexture.draw(textSfml);

				cursorPosition.y += 1;//get it pixel perfect

				rect.setPosition(cursorPosition);
				//	cout << cursorPosition.x << endl;
				if (cursorPosition.x < 0)
				{
					Vector2f currentPosition = textSfml.getPosition();
					currentPosition.x -= cursorPosition.x;
					cursorPosition.x = 0;
					textSfml.setPosition(currentPosition);
				}
				else if (cursorPosition.x > renderTexture.getSize().x)
				{
					Vector2f currentPosition = textSfml.getPosition();
					currentPosition.x -= (cursorPosition.x - renderTexture.getSize().x) + cursorWidth;
					cursorPosition.x = renderTexture.getSize().x - cursorWidth;
					textSfml.setPosition(currentPosition);
				}

				unsigned int k = textSfml.getCharacterSize();
				rect.setSize(Vector2f(cursorWidth, textSfml.getFont().getLineSpacing(k)));
				rect.setFillColor(Color::Magenta);
				renderTexture.draw(rect);


				renderTexture.display();
			}
			else if (elapsedTime < 0.5)
			{
				renderTexture.clear(Color::Transparent);
				renderTexture.draw(textSfml);
				renderTexture.display();

			}
			else {
				elapsedTime = 0;
			}

		}


		sf::Sprite sprite(renderTexture.getTexture());
		sprite.setPosition(windowPosition);

		RenderTexture j = RenderTexture(renderTexture.getSize());
		j.clear(Color::Cyan);

		Sprite G = Sprite(j.getTexture());
		G.setPosition(windowPosition);

		//	screenTexture->draw(G);//THIS PROOVES THAT THE PROBLEM WITH THE TEXTBOX IS BECAUSE THE SCREEN ISNT BEING CLEARED PROPERLY

		screenTexture->draw(sprite);//THIS IS BEING HIT FOREVER WHICH SHOULD NOT BE HAPPENING
		//window.display();
		return false;
	}

	void setPosition(Vector2f position)
	{
		position.x += 10;
		windowPosition = position;
		renderTexture.clear(sf::Color::Transparent);
		renderTexture.draw(textSfml);
		renderTexture.display();
	}
	void setSize(Vector2f size)
	{
		size.x -= 20;
		renderTexture.resize({ static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y) });
		windowSize = size;
		renderTexture.clear(sf::Color::Transparent);
		renderTexture.draw(textSfml);
		renderTexture.display();
	}
	void setText(string newText)
	{
		elapsedTime = 0;
		textSfml.setString(newText);

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