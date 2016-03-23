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

#define MAXLEVEL 10
#define PROB 2
using namespace std;

typedef struct skipNode {
	string key;
	int value;
	int height;
	struct skipNode *up;
	struct skipNode *down;
	struct skipNode *right;
	struct skipNode *left;

	skipNode(string k, int v) : key(k), value(v) {}
} skipNode;

typedef struct skipList {
	int height = 0;
	int size = 0;

	skipNode *head = new skipNode("",INT_MIN);
	skipNode *tail = new skipNode("",INT_MAX);

} skipList;

struct skipNode * skipSearch(skipList *current, int key) {
	skipNode *search = current->head;

	while (search->down != NULL) {
		search = search->down;
		while (key >= search->right->value) {
			search = search->right;
		}
	}
	return search;
}

/* Bad insert code. Needs improvement*/
void insert(skipList *current, string key, int data) {
	skipNode *newNode = new skipNode(key,data);
	skipNode *insertionPoint = skipSearch(current, data);

	newNode->right = insertionPoint->right;
	(insertionPoint->right)->left = newNode;
	insertionPoint->right = newNode;
	newNode->left = insertionPoint;
	current->size++;
	

	int coin;
	skipNode *temp = newNode;

	//Loop for stacking a node.
	while (1) {
		coin = rand() % 2;

		//If Coin Flip is bad we exit.
		if (!coin) break;

		//Stacking code.
		else {
			//Stack layer on top of newNode.
			skipNode *layer = new skipNode(key,data);
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

//Prints out the entire skip lists contents.
void print(skipList *current) {
	skipNode *node1 = current->head;
	
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

	/*Ensures randomness for insertion.*/
	//srand(time(NULL));
	srand(2);

	skipList *s = new skipList;

	/*Head is far right. Tail is far left.*/
	s->head->right = s->tail;
	s->tail->left = s->head;

	/*Base layer height is 0.*/
	s->head->height = 0;
	s->tail->height = 0;

	/*Temporary nodes to construct head and tail at all heights.*/
	skipNode *temp1 = s->head;
	skipNode *temp2 = s->tail;
	for (int i = 1; i < MAXLEVEL; ++i) {

		//Create next layer.
		temp1->up = new skipNode("",INT_MIN);
		temp2->up = new skipNode("",INT_MAX);

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

	string x = "key!";
	for (int i = 10; i > 0; --i) {
		int num = rand()%10;
		if (i != 5)
		insert(s,to_string(num)+x,num);
	}
	print(s);
	cout << skipSearch(s,7)->value << "\n";
	//cout << skipSearch(s,8) << "\n";
	//cout << skipSearch(s,10) << "\n";
	//cout << skipSearch(s,5) << "\n";
	
	return 0;
}