#include "pch.h"
#include "EText.h"
#include <SFML/OpenGL.hpp>

RenderTexture* EText::screenTexture = nullptr;
RenderWindow* EText::window = nullptr;

bool EText::draw()
	{
		screenTexture->setActive(true);
		bool cursorVisible = false;
		//store the gl scissor states so they can be reset if draws to other targets occure
		GLboolean scissorEnabled;
		GLint scissorBox[4];
		glGetBooleanv(GL_SCISSOR_TEST, &scissorEnabled);
		glGetIntegerv(GL_SCISSOR_BOX, scissorBox);

		//if (currentCharIndex != oldCharIndex && currentCharIndex != -1)//if the user has used the arrow keys to move in the string
		//{
		//	elapsedTime = 0;//make sure that the cursor is drawn
		//	oldCharIndex = currentCharIndex;
		//	cachedTexture.clear(Color::Transparent);
		//	cachedTexture.draw(textSfml);
		//	cachedTexture.display();
		//}


		if (currentCharIndex != -1)
		{
			elapsedTime += clock.restart().asSeconds();
			if (elapsedTime < 0.25) {
				cursorVisible = true;
			}
			else if (elapsedTime < 0.5)
			{
				cursorVisible = false;

			}
			else {
				elapsedTime = 0;
			}

		}

		if (currentCharIndex == -2)//magic number to indicate that the text needs to be redrawn without cursor
		{
			
			currentCharIndex = -1;
			cursorVisible = false;
		}

		Vector2u textureSize = cachedTexture.getSize();
		if (textureSize.x <= 0)
		{
			return false;
		}

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
		screenTexture->draw(quad, &cachedTexture);
		//draw the cursor over the text if it is visible
		if (cursorVisible)
		{
			CaretPosition cursorPosition = labelGenerator.charPosition(currentCharIndex);
			VertexArray cursor(sf::PrimitiveType::Lines, 2);
			cursor[0].position = Vector2f(windowPosition.x + cursorPosition.x, windowPosition.y + cursorPosition.y);
			cursor[1].position = Vector2f(windowPosition.x + cursorPosition.x, windowPosition.y + cursorPosition.y + cursorPosition.height);
			cursor[0].color = Color::Black;
			cursor[1].color = Color::Black;
			screenTexture->draw(cursor);
		}

		return false;
	}