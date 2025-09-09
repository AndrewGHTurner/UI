
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
	POST_DRAW_NEEDED = 1 << 5,
	IS_BRANCH = 1 << 6

};

enum PropertyFlagBits {
	HAS_MARGIN = 1 << 0
};

class UI;

/**
* @class TreeNode
* @brief Parent class of all nodes in the UI tree
* @details 
* @note 
*/
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
	
	
	
	uint8_t propertyFlags;
	Properties* properties;



	uint32_t id;
	uint8_t flags = 0;
	short numTexts = 0;
	TreeNode* parentNode = nullptr;//this is the Branch (container) that contains the widget

	void notifyTextChanged(bool added);//bool for if text object was added or not

	/**
	* @brief Sets the rendered position of the treeNode and notifies the parent of the change
	* @details Sets the origin, calculates the antiOrigin, and notifies the parent node that a recalculation is needed
	* @note Calculating the antiOrigin may be removed if the antiOrigin is removed to save memory
	* @param origin The new origin of the treeNode as x, y from the top left corner of the screen
	*/
	void setOrigin(Vector2f origin);

	/**
	* @brief Sets the rendered size of the treeNode and notifies the parent of the change
	* @details Sets the size, calculates the antiOrigin, and notifies the parent node that a recalculation is needed
	* @note Calculating the antiOrigin may be removed if the antiOrigin is removed to save memory
	* @param siz The new size of the treeNode as width, height
	*/
	void setSize(Vector2f siz);

	/**
	* @brief Shows if a 2d point on the screen is within this treeNode
	* @details Compares the point to the origin and antiOrigin of the treeNode
	* @note Implementation will have to change if the antiOrigin is removed to save memory
	* @param point The point to check if it is within the treeNode as x and y coordinates from the top left corner of the screen
	* @return true if the point is within the treeNode, otherwise false
	*/
	bool isPointWithin(Vector2i point);

	/**
	* @brief Sets flags to recalculate the vertices of this treeNode and it's parents
	* @details Notifies the parent to recalculate sizes of its children and to redraw them. A flag is set in this object and subsequent parents showing recalculation is needed. 
	* For each parent child layer a calcPositions method is called to calculate the positions of the children but the other children
	* wont have the recalculate flag set and so minimal computation is needed
	* Notification is done so that, in the
	* next frame, the UI can do the recalculation and redraw all changes at once which is more efficient than one at a time. The
	* biggest benefit with this system is when adding many leaves to a layout which would otherwise lead to many needless updates
	* @note Recalculation also redraws the elements
	*/
	void notifyRecalcNeeded();

	/**
	* @brief Sets flags to redraw this treeNode and its parents
	* @details Notifies parents and sets a flag so that the UI can redraw this treeNode at the next frame
	*/
	void notifyRedrawNeeded();

	//helper setters
	//IS_LEAF

	/**
	*@brief Sets the flag to show that this treeNode is a leaf
	*/
	inline void setIsLeafTrue() { flags |= IS_LEAF; }

	/**
	*@brief Sets the flag to show that this treeNode is a branch
	*/
	inline void setIsBranchTrue() { flags |= IS_BRANCH; }

	/**
	*@brief Sets the flag to show that this treeNode is not a leaf
	*/
	inline void setIsLeafFalse() { flags &= ~IS_LEAF; }

	/**
	*@brief Sets the flag to show that this treeNode is not a branch
	*/
	inline void setIsBranchFalse() { flags &= ~IS_BRANCH; }

	//REDRAW_NEEDED

	/**
	*@brief Sets the flag to show that redraw of this treeNode is needed
	*/
	inline void setRedrawNeededTrue() { flags |= REDRAW_NEEDED; }

	/**
	*@brief Sets the flag to show that redraw of this treeNode is not needed
	*/
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
	inline bool isBranch() const { return flags & IS_BRANCH; }
	inline bool isRedrawNeeded() const { return flags & REDRAW_NEEDED; }
	inline bool isRecalcNeeded() const { return flags & RECALC_NEEDED; }
	inline bool isRedrawTextNeeded() const { return flags & REDRAW_TEXT_NEEDED; }
	inline bool isPreDrawNeeded() const { return flags & PREE_DRAW_NEEDED; }
	inline bool isPostDrawNeeded() const { return flags & POST_DRAW_NEEDED; }
};

#endif
