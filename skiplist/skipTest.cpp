#include "skipList.hpp"
#include <ctime>

int main(int argc, char *argv[]) {

	skiplist *s = make_skiplist();			// Use this function to construct skiplists.
	int size = (argc == 2 ? atoi(argv[1]) : 500000);
	cout << "Using size: " << size << "\n";

	//Measure Insertion Time
	clock_t before = clock();
	for (int i = 1; i <= size; ++i) {
		insertNode(s,i);
	}
	clock_t after = clock();
	printf("Insertion Time: %.3lf seconds\n", double(after-before) / CLOCKS_PER_SEC);

	//Measure Search Time
	before = clock();
	for (int i = 1; i <= size; ++i) {
		skipSearch(s,i);
	}
	after = clock();
	printf("Search Time: %.3lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	//Measure Deletion Time
	before = clock();
	for (int i = 1; i <= size; ++i) {
		deleteNode(s,i);
	}
	after = clock();
	printf("Deletion Time: %.3lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	printf("Height Maximum Achieved: %d\n", s->head->height + 1);
	return 0;
}