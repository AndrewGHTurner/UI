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

### smoother resizing
When the user resizes the window the resize event from SFML is only fired when the mouse is released so there is no smooth resize. A possible solution
would be to poll window.getSize each frame

### Z index
Adding a Z index to elements would allow for overlapping elements and pop up windows etc. This needs some research to find the best way.
Ideas inclide a flat draw list sorted by z index or tree traversal with bounding box.

### Class to manage page show/hide automatically
ALTERNATIVLY pages could hold their own hash maps of callback lambdas. This is probably the more scalabe idea although would require editing
the UI class to support it. So the UI would have its own hash map for global callbacks and perhaps a vector of hashmaps for local callbacks for say a page or a composite widget
...CALLBACK REGISTRATION CONTEXT PER PAGE this could be set by the page switcher as a variable in the UI class. The developer would need
to remember to set the current contect during late callback registration only.... any rememberring is unnecessary if we guarantee
that there is always only one active page at a time.

Pages hold callback registries and the UI may have one for global callbacks. Input events are processed through the UI which is incharge of routing
events to the correct callback registry. The UI manages adding and removing callbacks via the inputController. This is based on the "active page" that
is set by classes such as pageSwitcher as then the developer of UIs does not need to specify the specific page for each callback.

# Design tradeoffs

## input controller
input controller holds callbacks and manages when they are called by being given the user input. Event routing is done by the UI class.
I have chosen composition so the UI class and page classes will hold an inputController instance. At the time of writing inheritance 
would also work but is less flexible long term.

For global events the element ID is set to zero. This means callbackMap keys only differ by event type so collisions are likely but number of 
global events will be low so this is acceptable.

## Lambda holders
CallbackLambdas take an EventData param. This allows for simple storage of lambdas but the API is slightly more annoying as all lambdas
need to take this param even if they do not use it. An alternative would be to have different lambda types for different events

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

## Crashing when the window closes

When you close the SFML window a memory access violation occurs. This is likely due to captured objects in lambdas being deleted before the lambda destructor is called.

## Text antialiasing

Sfml's text objects handle text rendering but they leave artifacts around the edges of the text making small text had to read. 

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