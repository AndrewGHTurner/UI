#ifndef LEAF_H
#define LEAF_H
#include "TreeNode.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
//this is a box that draws itself as UI ... 


class Leaf : public TreeNode
{
protected:

	VertexArray vertices;
public:
	static RenderTexture* screenTexture;
	void updateVerticesPosition()
	{
		int index = 0;
		//first triangle
		vertices[index].position = origin;
		vertices[index + 1].position = Vector2f(origin.x, antiOrigin.y);
		vertices[index + 2].position = Vector2f(antiOrigin.x, origin.y);
		//second triangle
		vertices[index + 3].position = Vector2f(antiOrigin.x, origin.y);
		vertices[index + 4].position = Vector2f(origin.x, antiOrigin.y);
		vertices[index + 5].position = Vector2f(antiOrigin.x, antiOrigin.y);

		//draw the vertices on the window

	//	notifyChange();
	}

	void draw()
	{
		screenTexture->draw(vertices);
		setRedrawNeededFalse();
		//	window->display();
	}

	static void setTexture(RenderTexture* newWindow)
	{
		screenTexture = newWindow;
	}

	Leaf(TreeNode* container) : TreeNode(container)
	{
		setIsLeafTrue();
		//allocate some vertices ... this should probs go into a child class
		vertices = VertexArray(sf::PrimitiveType::Triangles, 6);
	}
	//called when content changed each frame

};

#endif