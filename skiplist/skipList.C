/* Skip List by Aedan Burnett */

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <tuple>
#include <cmath>
#include <utility>
#include <string>
#include <climits>

#define MAXLEVEL 10	// No node may go higher than 10 stacks.
#define PROB 2 		// 1/PROB chance of stacking a node.

using namespace std;

template <typename T> T compare(T a, T b) {
	return a >= b;
}

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
	int height = 0;
	int size = 0;

	skipnode *head = new skipnode(INT_MIN);
	skipnode *tail = new skipnode(INT_MAX);

} skiplist;

/* Creates an empty skiplist struct and initializes its values properly */
struct skiplist * make_skiplist() {

	skiplist *s = new skiplist;

	/*Head is far right. Tail is far left.*/
	s->head->right = s->tail;
	s->tail->left = s->head;

	/*Base layer height is 0.*/
	s->head->height = 0;
	s->tail->height = 0;

	/*Temporary nodes to construct head and tail at all heights.*/
	skipnode *temp1 = s->head;
	skipnode *temp2 = s->tail;
	for (int i = 1; i < MAXLEVEL; ++i) {

		//Create next layer.
		temp1->up = new skipnode(INT_MIN);
		temp2->up = new skipnode(INT_MAX);

		//Set next layer height.
		temp1->up->height = i;
		temp2->up->height = i;

		//Set next layer to be head and tail to each other.
		temp1->up->right = temp2->up;
		temp2->up->left = temp1->up;

		//The new level should refer to the old.
		(temp1->up)->down = temp1;
		(temp2->up)->down = temp2;

		//Set the current node to be the new level.
		temp1 = temp1->up;
		temp2 = temp2->up;
	}
	//Finally. The head should be at the top of the list.
	s->head = temp1;
	s->tail = temp2;
	return s;
}

/* Returns a pointer to the highest node <= K */
struct skipnode * skipSearch(skiplist *current, int K) {
	skipnode *search = current->head;

	while (search->down != NULL) {
		search = search->down;
		while (K >= search->right->value) {
			search = search->right;
		}
	}
	return search;
}

/* Inserts a skipnode into the list. Has a 1/PROB chance of stacking it. */
void insertNode(skiplist *current, int data) {
	skipnode *newNode = new skipnode(data);
	skipnode *insertionPoint = skipSearch(current, data);

	newNode->right = insertionPoint->right;
	(insertionPoint->right)->left = newNode;
	insertionPoint->right = newNode;
	newNode->left = insertionPoint;
	current->size++;
	

	int coin;
	skipnode *temp = newNode;

	//Loop for stacking a node.
	while (1) {
		coin = rand() % PROB;

		//A good 'coinflip' is 0. All other values do not stack.
		if (coin) break;

		//Stacking code.
		else {
			//Stack layer on top of newNode.
			skipnode *layer = new skipnode(data);
			temp->up = layer;
			layer->down = temp;
			layer->height = temp->height+1;

			/*Find layers left node*/
			while (layer->down != NULL) {
				layer = layer->down;
			}	

			while (layer->height != temp->height+1) {
				layer = layer->left;
				while (layer->up != NULL 
					and layer->height != temp->height+1) {
					layer = layer->up;
				}
			}

			temp->up->left = layer;
			layer->right = temp->up;
			layer = temp->up;

			/*Find layers right node */
			while (layer->down != NULL) {
				layer = layer->down;
			}	

			while (layer->height != temp->height+1) {
				layer = layer->right;
				while (layer->up != NULL 
					and layer->height != temp->height+1) {
					layer = layer->up;
				}
			}

			temp->up->right = layer;
			layer->left = temp->up;

			/*Temp is now the stacked layer*/
			temp = temp->up;
		}
		if (temp->height >= MAXLEVEL-1) {
			break;
		}
	}
}

/* Deletes the last occurence of a node and all of its stacks. Returns -1 on failure, 1 on success */
int deleteNode(skiplist *current, int data) {
	skipnode *deletionPoint = skipSearch(current, data);
	if (deletionPoint->value != data) return -1;
	
	while (deletionPoint->up != NULL) {
		deletionPoint->left->right = deletionPoint->right;
		deletionPoint->right->left = deletionPoint->left;
		deletionPoint = deletionPoint->up;
		free(deletionPoint->down);
		deletionPoint->down = NULL;
	}		
	deletionPoint->left->right = deletionPoint->right;
	deletionPoint->right->left = deletionPoint->left;
	free(deletionPoint->down);
	deletionPoint->down = NULL;
	free(deletionPoint);
	current->size--;
	return 1;
}

/*Prints out the entire skip lists contents.*/
void print(skiplist *current) {
	skipnode *node1 = current->head;
	
	while (node1->down != NULL) {
		while (node1->right != NULL) {
			cout << node1->value << " ";
			node1 = node1->right;
		}
		cout << node1->value << "\n";
		node1 = node1->down;

		while (node1->left !=NULL) {
			node1 = node1->left;
		}
	}

	while (node1->right != NULL) {
			cout << node1->value << " ";
			node1 = node1->right;
		}
	cout << node1->value << "\n";
}

int main() {

	srand(time(NULL));						// Sets a seed based on systime for randomness.
	skiplist *s = make_skiplist();			// Use this function to construct skiplists.

	for (int i = 500000; i > 0; --i) {
		insertNode(s,i);
	}
	for (int i = 50; i > 0; --i) {
		int x = skipSearch(s,i)->value;
	}
	
	return 0;
}