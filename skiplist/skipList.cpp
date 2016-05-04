/* Skip List by Aedan Burnett */
#include "skipList.hpp"

/* Creates an empty skiplist struct and initializes its values properly */
struct skiplist * make_skiplist() {

	srand(time(NULL));						// Sets a seed based on systime for randomness.
	skiplist *s = new skiplist;

	/*Head is far right. Tail is far left.*/
	s->head->right = s->tail;
	s->tail->left = s->head;

	/*Base layer height is 0.*/
	s->head->height = 0;
	s->tail->height = 0;

	/*Base layer down is NULL*/
	s->head->down = NULL;
	s->tail->down = NULL;

	/*Temporary nodes to construct head and tail at all heights.*/
	skipnode *temp1 = s->head;
	skipnode *temp2 = s->tail;
	for (int i = 1; i < s->maxheight; ++i) {

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
	s->head->up = NULL;
	s->tail->up = NULL;
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
	newNode->down = NULL;
	newNode->up = NULL;
	current->size++;
	
	// Maxheight should be max(10,2[logn]) and may need adjustment
	if ( (int)2*ceil(log(current->size)) > current->maxheight ) {
		increaseHeight(current, (int)2*ceil(log(current->size)));
	}

	int coin;
	skipnode *temp = newNode;

	//Loop for stacking a node.
	while (1) {
		coin = rand() % PROB;

		//A good 'coinflip' is 0. All other values do not stack.
		if (coin) {
			temp->up = NULL;
			break;
		}

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

			while (layer->height != temp->height+1 and layer->left != NULL) {
				layer = layer->left;
				while (layer->up != NULL and layer->height != temp->height+1) {
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

			while (layer->height != temp->height+1 and layer->right != NULL) {
				layer = layer->right;
				while (layer->up != NULL and layer->height != temp->height+1) {
					layer = layer->up;
				}
			}

			temp->up->right = layer;
			layer->left = temp->up;

			/*Temp is now the stacked layer*/
			temp = temp->up;
		}

		if (temp->height >= current->maxheight - 1) {
			temp->up = NULL;
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

/* Increases Maximum Height of the Skip List to h. */
void increaseHeight(skiplist *current, int h) {
	current->maxheight = h;
	skipnode *temp1 = current->head;
	skipnode *temp2 = current->tail;

	while (temp1->height < h - 2) {
		//Create next layer.
		temp1->up = new skipnode(INT_MIN);
		temp2->up = new skipnode(INT_MAX);

		//Set next layer height.
		temp1->up->height = temp1->height + 1;
		temp2->up->height = temp2->height + 1;

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
	current->head = temp1;
	current->tail = temp2;
	current->head->up = NULL;
	current->tail->up = NULL;
}

/*Prints out the entire skip lists contents.*/
void skipPrint(skiplist *current) {
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