# UI Library

## This library is a work in progress!!! 

This is a UI library written on top of the SFML 2D graphics library.
SFML is used only for rendering triangles and text,
but handling vertex arrays etc. is done by the UI library itself,
so it can be ported to OpenGL or Vulkan in the future.

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