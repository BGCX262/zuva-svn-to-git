#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define DEBUG 0

void print_reverse(vector<int> & stack) {
	ostream_iterator<int> output(cout, " ");
	copy(stack.rbegin(), stack.rend(), output);
	cout << endl;
}

void flip(vector<int> & stack, int begin) {
	if (begin == stack.size()) {
		cout << 0 << endl;
		return;
	}
	/**
	 * find the max one
	 */
	int i, maxInd = begin - 1, maxVal = stack[maxInd];
	for (i = begin - 1; i < stack.size(); i++) {
		if (maxVal < stack[i]) {
			maxInd = i;
			maxVal = stack[i];
		}
	}
	if (maxInd == begin - 1) {
		/**
		 * max pancake has already in the bottom
		 */
	} else if (maxInd == stack.size() - 1) {
		/**
		 * max pancake is in the top
		 */
		reverse(stack.begin() + begin - 1, stack.end());
		cout << begin << " ";
	} else {
		/**
		 * flip max one to the bottom
		 */
		reverse(stack.begin() + maxInd, stack.end());
		cout << maxInd + 1 << " ";
		reverse(stack.begin() + begin - 1, stack.end());
		cout << begin << " ";
	}
	flip(stack, begin + 1);
}

int main(int argc, char * argv[]) {
	string sline;
	int nDia;
	while (getline(cin, sline)) {
		istringstream is(sline);
		vector<int> stack;
		while (is >> nDia) {
			stack.insert(stack.begin(), nDia);
		}
		print_reverse(stack);
		flip(stack, 1);
	}
	return 0;
}

