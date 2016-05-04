# 403-Research-Project
Implementation of SkipList Data Structure in C/C++.

The skiplist is a data structure similar to a linked list that is used to
contain a sorted list of items. You can insert, search and delete items all
in logarithmic time making its functionality very similar to a set. There is
a random element to it since it's randomly determined how high to stack an item. I chose to use P = 0.5 and Max Height = max(10, 2(ceiling(log(n)))) since the papers I read suggested this was the best for performance. 

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
	void skipPrint(skiplist *current);


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
		Insertion Time: 0.003 seconds
		Search Time: 0.001 seconds
		Deletion Time: 0.001 seconds

	100,000 Items
		Insertion Time: 0.036 seconds
		Search Time: 0.020 seconds
		Deletion Time: 0.014 seconds
	
	500,000 Items
		Insertion Time: 0.190 seconds
		Search Time: 0.106 seconds
		Deletion Time: 0.077 seconds

C++ Set

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

With my latest changes, the Skiplist now consistently outperforms a C++ set!

The variance isn't huge, but at even the smallest of values it consistently shaves off time. 

Ignoring the fact that the space complexity is probably poor, the overall utility is impressive.

--------------------------------
CITATIONS
--------------------------------

https://www.ics.uci.edu/~pattis/ICS-23/lectures/notes/Skip%20Lists.pdf

http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/skip-list-impl.html - (None of the limited Java Code shown on this page was used, just the graphics/explanations for reference.)

--------------------------------
LICENSING
--------------------------------

Copyright 2016 Aedan Burnett

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
