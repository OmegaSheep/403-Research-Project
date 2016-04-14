# 403-Research-Project
Implementation of SkipList Data Structure in C/C++.

--------------------------------
FILE STRUCTURE
--------------------------------
	
	skiplist/
		makefile
		skipList.cpp
		skipList.hpp
		skipTest.cpp
	
	set/
		makefile
		setTest.cpp

--------------------------------
USING MY TESTS
--------------------------------

I have included a test program for skiplists as well as a test program for the C++ <set> library (for comparison purposes).

In the proper directory simply use "make" to compile my tests.

Run using " > ./skipTest [INPUT SIZE]" or " > ./setTest [INPUT SIZE]" accordingly.

The tests will time and perform 3 operations: Inserting [INPUT SIZE] items, searching for every item and deleting every item.

NOTE: If a size is not provided then the default test size of 500,000 will be used.

--------------------------------
USAGE WITH YOUR OWN PROGRAMS
--------------------------------

To use skipLists in your program include "skipList.hpp" in your main file and compile your program with "skipList.cpp".

In addition to the structs "skipnode" and "skiplist" the following 5 functions are defined:

	//Creates an empty skiplist struct and initializes its values properly
	struct skiplist * make_skiplist();

	//Returns a pointer to the highest node <= K
	struct skipnode * skipSearch(skiplist *current, int K);

	//Inserts a skipnode into the list. Has a 1/PROB chance of stacking it up to 10 times
	void insertNode(skiplist *current, int data);

	//Deletes the last occurence of a node and all of its stacks. Returns -1 on failure, 1 on success
	int deleteNode(skiplist *current, int data);

	//Prints out the entire skip lists contents. Note that MIN_INT and MAX_INT are used to represent the left and right boundaries, which are also printed.
	void print(skiplist *current);


--------------------------------
EXPECTED PERFORMANCE (BIG O-NOTATION)
--------------------------------

Skiplist

	Insert - O(log(n))
	Search - O(log(n))
	Delete - O(log(n))

C++ Set

	Insert - O(log(n))
	Search - O(log(n))
	Delete - O(log(n))

--------------------------------
ACTUAL PERFORMANCE
--------------------------------

Skiplist

	100 Items
		Insertion Time: 0.000 seconds
		Search Time: 0.000 seconds
		Deletion Time: 0.000 seconds

	10,000 Items
		Insertion Time: 0.002 seconds
		Search Time: 0.002 seconds
		Deletion Time: 0.002 seconds

	100,000 Items
		Insertion Time: 0.019 seconds
		Search Time: 0.111 seconds
		Deletion Time: 0.125 seconds
	
	500,000 Items (Observed Variance: ~ +0.6 seconds)
		Insertion Time: 0.100 seconds
		Search Time: 7.416 seconds
		Deletion Time: 7.471 seconds

Set

	100 Items
		Insertion Time: 0.000 seconds
		Search Time: 0.000 seconds
		Deletion Time: 0.000 seconds
	
	10,000 Items
		Insertion Time: 0.004 seconds
		Search Time: 0.002 seconds
		Deletion Time: 0.003 seconds
	
	100,000 Items
		Insertion Time: 0.051 seconds
		Search Time: 0.028 seconds
		Deletion Time: 0.037 seconds
	
	500,000 Items
		Insertion Time: 0.293 seconds
		Search Time: 0.162 seconds
		Deletion Time: 0.216 seconds

--------------------------------
CONCLUDING THOUGHTS
--------------------------------

The good news is that the skiplist seems to compete very effectively with the C++ set even up to inputs of size 100,000. In particular,
the insertion time remains CONSISTENTLY better for all sizes of input.

However at the 500,000 mark, the skiplist begins to struggle greatly performing almost 40 times slower on a bad run for searching and deleting items.

The variance also appears to increase somewhat; I've observed run times as high as 8.230s for the largest input size.

I think a lot of this comes from slightly inefficient pointer usage, but I'm impressed at its speed for small-medium inputs.

--------------------------------
CITATIONS
--------------------------------

https://www.ics.uci.edu/~pattis/ICS-23/lectures/notes/Skip%20Lists.pdf

http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/skip-list-impl.html - (None of the limited Java Code shown on this page was used, just the graphics/explanations for reference.)
