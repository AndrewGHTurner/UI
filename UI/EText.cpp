#include "pch.h"
#include "EText.h"
#include <SFML/OpenGL.hpp>

RenderTexture* EText::screenTexture = nullptr;
RenderWindow* EText::window = nullptr;

bool EText::draw()
	{
		screenTexture->setActive(true);
		//store the gl scissor states so they can be reset if draws to other targets occure
		GLboolean scissorEnabled;
		GLint scissorBox[4];
		glGetBooleanv(GL_SCISSOR_TEST, &scissorEnabled);
		glGetIntegerv(GL_SCISSOR_BOX, scissorBox);

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

		Vector2u textureSize = cachedTexture.getSize();
		if (textureSize.x <= 0)
		{
			return false;
		}

		Texture textTexture = cachedTexture.getTexture();

		VertexArray quad(sf::PrimitiveType::Triangles, 6);
		quad[0].position = Vector2f(windowPosition.x, windowPosition.y);
		quad[1].position = Vector2f(windowPosition.x + textureSize.x, windowPosition.y);
		quad[2].position = Vector2f(windowPosition.x + textureSize.x, windowPosition.y + textureSize.y);
		quad[3].position = Vector2f(windowPosition.x, windowPosition.y);
		quad[4].position = Vector2f(windowPosition.x + textureSize.x, windowPosition.y + textureSize.y);
		quad[5].position = Vector2f(windowPosition.x, windowPosition.y + textureSize.y);

		quad[0].texCoords = Vector2f(0, 0);
		quad[1].texCoords = Vector2f(textureSize.x, 0);
		quad[2].texCoords = Vector2f(textureSize.x, textureSize.y);
		quad[3].texCoords = Vector2f(0, 0);
		quad[4].texCoords = Vector2f(textureSize.x, textureSize.y);
		quad[5].texCoords = Vector2f(0, textureSize.y);
		
		//reinstate scissor states in case the draw calls above reset them
		screenTexture->setActive(true);
		// Apply scissor + correct viewport!
		glViewport(0, 0, screenTexture->getSize().x, screenTexture->getSize().y);
		screenTexture->resetGLStates();
		if (scissorEnabled) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
		}
		else {
			glDisable(GL_SCISSOR_TEST);
		}
		//must draw a vertex arrary rather than a sprite to preserve the scissor states
		screenTexture->draw(quad, &cachedTexture.getTexture());

		return false;
	}