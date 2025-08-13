
#ifndef TREENODE_H
#define TREENODE_H
#include <SFML/System/Vector2.hpp>
#include "Box.h"
#include <cstdint>
#include "Properties.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include "UI_DLL_Interface.h"
using namespace sf;

enum TreeNodeFlagBits {
	IS_LEAF = 1 << 0,
	REDRAW_NEEDED = 1 << 1,
	RECALC_NEEDED = 1 << 2,
	REDRAW_TEXT_NEEDED = 1 << 3,
	PREE_DRAW_NEEDED = 1 << 4,
	POST_DRAW_NEEDED = 1 << 5

};

enum PropertyFlagBits {
	HAS_MARGIN = 1 << 0
};

class UI;

//TreeNode in the UI tree
class UI_API TreeNode : public Box {

public:
	static sf::RenderTexture* screenTexture;
	TreeNode(const TreeNode&) = delete;             // disable copy constructor
	TreeNode& operator=(const TreeNode&) = delete;  // disable copy assignment
//	TreeNode(TreeNode&&) noexcept = default;        // enable move constructor
//	TreeNode& operator=(TreeNode&&) noexcept = default; // enable move assignment
	bool hasText = false;//THIS FLAG SHOULD GO IN flags
	TreeNode();
	TreeNode(TreeNode* parent);
	TreeNode(Vector2f origin, Vector2f size);
	TreeNode(TreeNode* parent, Vector2f origin, Vector2f siz);
	static UI* ui;
	
	
	
	uint8_t propertyFlags;
	Properties* properties;



	uint32_t id;
	uint8_t flags = 0;
	short numTexts = 0;
	TreeNode* parentNode = nullptr;//this is the Branch (container) that contains the widget

	void notifyTextChanged(bool added);//bool for if text object was added or not
	//change the rendered position of the node and notify parent
	void setOrigin(Vector2f origin);
	//change the rendered size of the node and notify parent
	void setSize(Vector2f siz);
	bool isPointWithin(Vector2i point);

	//notify any changes in the positions of the verticies in the vertex array
	//this allows vertices to be updated at most once per frame which is more efficient if adding many leaves to a layout
	void notifyRecalcNeeded();
	void notifyRedrawNeeded();
	//helper setters
	inline void setIsLeafTrue() { flags |= IS_LEAF; }
	inline void setIsLeafFalse() { flags &= ~IS_LEAF; }
	//REDRAW_NEEDED
	inline void setRedrawNeededTrue() { flags |= REDRAW_NEEDED; }
	inline void setRedrawNeededFalse() { flags &= ~REDRAW_NEEDED; }
	//RECALC_NEEDED
	inline void setRecalcNeededTrue() { flags |= RECALC_NEEDED; }
	inline void setRecalcNeededFalse() { flags &= ~RECALC_NEEDED; }
	//REDRAW_TEXT_NEEDED
	inline void setRedrawTextNeededTrue() { flags |= REDRAW_TEXT_NEEDED; }
	inline void setRedrawTextNeededFalse() { flags &= ~REDRAW_TEXT_NEEDED; }
	//PREE_DRAW_NEEDED
	inline void setPreDrawNeededTrue() { flags |= PREE_DRAW_NEEDED; }
	inline void setPreDrawNeededFalse() { flags &= ~PREE_DRAW_NEEDED; }
	//POST_DRAW_NEEDED
	inline void setPostDrawNeededTrue() { flags |= POST_DRAW_NEEDED; }
	inline void setPostDrawNeededFalse() { flags &= ~POST_DRAW_NEEDED; }
	//helper testers
	inline bool isLeaf() const { return flags & IS_LEAF; }
	inline bool isRedrawNeeded() const { return flags & REDRAW_NEEDED; }
	inline bool isRecalcNeeded() const { return flags & RECALC_NEEDED; }
	inline bool isRedrawTextNeeded() const { return flags & REDRAW_TEXT_NEEDED; }
	inline bool isPreDrawNeeded() const { return flags & PREE_DRAW_NEEDED; }
	inline bool isPostDrawNeeded() const { return flags & POST_DRAW_NEEDED; }
};

#endif
