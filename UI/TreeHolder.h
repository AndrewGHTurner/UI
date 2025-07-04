//#define 

/*
make a tree holder class which will just hold a bunch of ui trees and allow one to be displayed

make a tree builder class which hold methods to build trees and display one

WHEN A TREE IS DESTROED REMEMBER TO DELETE THE CLICK HANDELERS ETC AS WILL HAVE NEW IDS WHEN REBUILT ... COLOURED BOX DESTRUCTOR?

make a page class which will hold a ui tree and the method to create it

make a page holder class which will hold a bunch of pages and allow one to be displayed


*/

/*
frame facade that holds a tree holder and a tree builder? ... can be used even if no method exists that builds the tree


page just holds the ui tree and the method to create it 


- if just method ... go into tree builder
- if just tree ... go into tree holder
- if both put in both but check tree holder first ... prooblem with ids ... would need an extra datastructure to hold methods
*/



/*
make tree holder class ... fast
make tree builder class ... memory efficient
make page holder class ... could be instructed to destroy trees to save memory or to create them for speed. Page is a nice abstraction.
	allows for the creation of multipage uis without building all the trees at once

	Page class could hold IDs?


	The frame facade idea is bad because it needs logic to deal with the ids etc not worth it
*/