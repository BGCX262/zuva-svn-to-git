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

/**
 * rows number n = (2/sqr(3))*(height-1) + 1
  * if(wideth - m ) > r then
 *    all number = m*n
 *  else
 *    all number = m*n - n/2
 */
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

