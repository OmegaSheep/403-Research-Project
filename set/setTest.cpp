#include <set>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;
int main(int argc, char *argv[]) {

	set<int> s;


	int size = (argc == 2 ? atoi(argv[1]) : 500000);
	cout << "Using size: " << size << "\n";

	//Measure Insertion Time
	clock_t before = clock();
	for (int i = 1; i <= size; ++i) {
		s.insert(i);
	}
	clock_t after = clock();
	printf("Insertion Time: %.3lf seconds\n", double(after-before) / CLOCKS_PER_SEC);

	//Measure Search Time
	before = clock();
	for (int i = 1; i <= size; ++i) {
		s.find(i);
	}
	after = clock();
	printf("Search Time: %.3lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	//Measure Deletion Time
	before = clock();
	for (int i = 1; i <= size; ++i) {
		s.erase(i);
	}
	after = clock();
	printf("Deletion Time: %.3lf seconds\n",double(after-before) / CLOCKS_PER_SEC);

	return 0;
}