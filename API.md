This file describes the minimum API data structures of different 
types (maps, arrays, lists, trees, etc) should expose if they are to 
conform to my "standard".  There may be both const and non-const versions
of these methods; I haven't decided yet.  Eventually I think I'll try to 
make sure everything that should reasonably be mutable has a mutable option.h

I'll try to remember to add things to this list as I start implementing them.
Not everything is (or will in a timely fashion) conform to this API.

List types
============
Includes: LinkedList, Deque  

Methods:
<ul>
	<li>append : Adds an item to the end of the list</li>
	<li>getHead : Returns the first item in the list</li>
	<li>getTail : Returns the last item in the list</li>
	<li>remove : Removes an item from the list</li>
	<li>pop : Removes and returns an item from the list</li>
	<li>size : Returns the number of elements in the list</li>
	<li>isEmpty : Returns whether the list is empty</li>
	<li>subscript ([]) : Allows indexing of the list</li>
	<li><< : Allows writing the list to a stream (ie as a string)</li>
	<li>sort : Sorts the list (modifies the list)</li>
	<li>reverse : Reverses the list (modifies the list)</li>
	<li>sorted : Returns a sorted copy of the list (list is unchanged)</li>
	<li>reversed : Returns a reversed copy (original is unchanged)</li>
</ul>

Mapping types
=============
Includes: Map

Methods:
<ul>
	<li>keys : Returns the keys in the map</li>
	<li>values : Returns the values in the map</li>
	<li>items : Returns the key-value pairs in the map</li>
	<li>isEmpty : Returns whether the map is empty</li>
	<li>size : Returns the number of key-value pairs in the map</li>
	<li>add : Adds a key-value pair to the map</li>
	<li>remove : Removes a key-value pair from the map</li>
	<li>pop : Removes and returns a key-value pair from the map</li>
	<li>update : Updates the value associated with a key</li>
</ul>
