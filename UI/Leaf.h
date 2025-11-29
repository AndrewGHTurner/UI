#ifndef LEAF_H
#define LEAF_H
#include "TreeNode.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "UI_DLL_Interface.h"
#include <SFML/OpenGL.hpp>
//this is a box that draws itself as UI ... 

/**
 * @brief Leaf is a TreeNode that can draw itself ... widgets are can be created by subclassing this
 * @details Subclasses can change the widget's appearance by controlling the vertices VertexArray
 *
 */
class UI_API Leaf : public TreeNode
{
protected:

	VertexArray vertices;
public:
	
	virtual void updateVerticesPosition()
	{
		//first triangle
		vertices[0].position = origin;
		vertices[1].position = Vector2f(origin.x, antiOrigin.y);
		vertices[2].position = Vector2f(antiOrigin.x, origin.y);
		//second triangle
		vertices[3].position = Vector2f(antiOrigin.x, origin.y);
		vertices[4].position = Vector2f(origin.x, antiOrigin.y);
		vertices[5].position = Vector2f(antiOrigin.x, antiOrigin.y);

		//draw the vertices on the window

	//	notifyChange();
	}

	void draw()
	{
		screenTexture->draw(vertices);
		setRedrawNeededFalse();
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

	Leaf() : TreeNode(nullptr)
	{
		setIsLeafTrue();
		vertices = VertexArray(sf::PrimitiveType::Triangles, 6);//@todo move to child class
	}
	virtual ~Leaf() = default;
	//called when content changed each frame

};

#endif