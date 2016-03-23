#include <set>
#include <iostream>
#include <climits>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main() {

	set<int> s;

	for (int i = 500000; i > 0; --i) {
		s.insert(i);
	}
	for (int i = 50; i > 0; --i) {
		auto it = s.find(i);
	}
	return 0;
}