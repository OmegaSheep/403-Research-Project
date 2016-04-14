#include "skipList.hpp"
#include <ctime>

int main(int argc, char *argv[]) {

	skiplist *s = make_skiplist();			// Use this function to construct skiplists.

	int size = (argc == 2 ? atoi(argv[1]) : 500000);
	cout << "Using size: " << size << "\n";

	//Measure Insertion Time
	clock_t before = clock();
	for (int i = size; i > 0; --i) {
		insertNode(s,i);
	}
	clock_t after = clock();
	printf("Insertion Time: %.2lf seconds\n", double(after-before) / CLOCKS_PER_SEC);

	//Measure Search Time
	before = clock();
	for (int i = size; i > 0; --i) {
		skipSearch(s,i);
	}
	after = clock();
	printf("Search Time: %.2lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	//Measure Deletion Time
	before = clock();
	for (int i = size; i > 0; --i) {
		deleteNode(s,i);
	}
	after = clock();
	printf("Deletion Time: %.2lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	return 0;
}