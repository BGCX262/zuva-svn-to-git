#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG 0

struct Student {
	int num;
	int pay;
	Student(int n) {
		num = n;
		pay = 0;
	}
};

int main(int argc, char * argv[]) {
	int n, k;
	while (true) {
		cin >> n;
		cin >> k;
		if (n == 0 && k == 0)
			break;

		int outStore = 1;
		int outIndex = 1;
		queue<struct Student> qu;
		for (int i = 0; i < n; i++) {
			qu.push(Student(i + 1));
		}
		while (qu.size() > 0) {
			Student stu = qu.front();
			qu.pop();

			if (DEBUG) {
				cout << "before ! stu:" << stu.num << " pay:" << stu.pay << "  outStore:" << outStore << " outIndex:" << outIndex << endl;
			}

			if (outStore + stu.pay <= 40) {
				stu.pay += outStore;
				outStore = 0;
			} else {
				outStore = outStore + stu.pay - 40;
				stu.pay = 40;
			}

			if (outStore == 0) {
				outIndex++;
				if (outIndex > k) {
					outIndex = 1;
				}
				outStore = outIndex;
			}
			if (DEBUG) {
				cout << "after ! stu:" << stu.num << " pay:" << stu.pay << "  outStore:" << outStore << " outIndex:" << outIndex << endl;
			}

			if (stu.pay == 40) {
				if (DEBUG) {
					cout << "stu:" << stu.num << " has reached 40!" << endl;
				} else {
					cout << setw(3) << stu.num;
				}
			} else {
				qu.push(stu);
			}
		}
		cout << endl;
	}

	return 0;
}
