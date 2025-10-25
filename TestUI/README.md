# UI Library

## This library is a work in progress!!! 

This is a UI library written on top of the SFML 2D graphics library.
SFML is used only for rendering triangles and text,
but handling vertex arrays etc. is done by the UI library itself,
so it can be ported to OpenGL or Vulkan in the future.

# Futute features to add

### Custom rendering - for games and simulations
An class similar to Animation.h and a manager class that would allow for the definition of per frame rendering of custom 
elements before the UI is drawn to the screen. This would allow for simulation visualizations etc.

### UI interpreted language and interpreter
Creating a language to define UIs that is interpreted would allow for more dynamic UIs that could more easily be altered at runtime. An interpreted
UI definition language (similar to HTML/CSS) could potentially massively improve development time at the cost of performance... although the
performance penalty will be negligible for most UIs.

# Design tradeoffs

## Lambda callback IDs

Two main ways to handle callback IDs:

### uint_8t IDs
Pros:
	3 bytes less memory than an 32 bit int ID
Cons:
	Can only have 255 callbacks per element although this number is unlikely to be reached
	Much harder to manage keeping track of open IDs when lambdas are added and removed
	Lambdas for different elements could have the same ID so collection of relevant lambdas for an event would need to check the element ID as well as the lambda ID

### 32 bit int IDs
pros:
	Allow for many many callbacks per element
	Easy to manage getting new IDs by having a monotonically increasing counter
cons:
	Uses 3 bytes more memory per callback ID
	Wrapping of IDs back to zero will occur after 4,294,967,295 lambda callbacks are created ... This number is unlikely to be reached
This library uses 32 bit int IDs due to their ease of management. The extra memory usage is not significant on modern systems. It must
be noted that if ID wrapping occurs bugs would start to appear as different lambdas would have the same ID. This will only be a problem
in huge or very long lived and dynamic UIs. To achieve a UI that could create and destroy over 4 billion lambda callbacks the uint8_t 
system with an intelligent way of tracking unused IDs would be needed. 

# Known issues

## Lambda callback lifetimes

Currently release callbacks are stored in a vector of references to relevant callbacks when the mouse is clicked. This can cause undefined
behavior if a callback is removed while the mouse is held down. Copying callbacks to the vector would not solve the problem as they may
act on deleted elements.

### Planned fix

When the user clicks all calls to the UI to remove lambdas should instead store them in a cache to be deleted. When running release
callbacks any callbacks represented in this cache should not be run(because they have been deleted from the developer's point of view).
Once the mouse has been release then the callbacks in the cache should actually be deleted.

## Horizontal splitter mouse cursor

The mouse cursor logic works for an individual handle element. ie it changes correctly to the drag curser when dragging and hovering.
However, the cursor can be incorrectly changed back to the pointer while dragging if the mouse moves over another handle element, causing
its lambda to be called. This is a minor issue as the dragging still works correctly.

### Planned fix

A singleton object that controls the mouse cursor state would allow the state to be locked by a single element. Any irrelevant lambda
calls to the object to change the cursor would be ignored while locked.

## Thin textBox

A textBox with a height less than the text size will not render correctly and the text will shake.

## Excessive redraw

If a layout low down in the UI tree needs to recalculate it will notify its parent etc. This works but it leads to all parent layouts
also recalculating which leads to the whole screen redrawing which is inefficient.

## Text Not Redrawn on navigation to a page

Currentlt setRedrawTextFalse is commented out on ~line 160 of Branch.h so that text is always redrawn... this leads to too many draws but means navigatoin works.
To solve this a method should be made to navigate the UI tree when a page is navigated to and set redaw text needed to true befor draw.