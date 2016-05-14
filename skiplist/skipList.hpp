/*Copyright 2016 Aedan Burnett

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */


#ifndef _SKIP_LIST_H_INCLUDED
#define _SKIP_LIST_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <climits>

#define PROB 2 		// 1 / PROB chance of stacking a node.

using namespace std;

typedef struct skipnode {
	int value;
	int height;
	struct skipnode *up;
	struct skipnode *down;
	struct skipnode *right;
	struct skipnode *left;

	skipnode(int v) : value(v) {}
} skipnode;

typedef struct skiplist {
	int maxheight = 10;
	int size = 0;

	skipnode *head = new skipnode(INT_MIN);
	skipnode *tail = new skipnode(INT_MAX);

} skiplist;

/* Creates an empty skiplist struct and initializes its values properly */
struct skiplist * make_skiplist();

/* Returns a pointer to the highest node <= K */
struct skipnode * skipSearch(skiplist *current, int K);

/* Inserts a skipnode into the list. Has a 1/PROB chance of stacking it. */
void insertNode(skiplist *current, int data);

/* Deletes the last occurence of a node and all of its stacks. Returns -1 on failure, 1 on success */
int deleteNode(skiplist *current, int data);

/* Increases the maxheight of the skiplist to h. Called by insertion method. */
void increaseHeight(skiplist *current, int h);

/*Prints out the entire skip lists contents.*/
void skipPrint(skiplist *current);

#endif
