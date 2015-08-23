#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
using namespace std;

static int num, kth;

struct Person {
	int nu;
	struct Person * next;
	struct Person * pre;
};

struct Person * init() {
	struct Person * p1 = new struct Person();
	p1->nu = 1;
	struct Person * p2 = p1;
	for (int i = 2; i <= num; i++) {
		p2->next = new struct Person();
		p2->next->nu = i;
		p2->next->pre = p2;
		p2 = p2->next;
	}
	p2->next = p1;
	p1->pre = p2;
	return p1;
}

int main(int argc, char * argv[]) {
	string str;
	while (getline(cin, str)) {
		num = 0;
		kth = 0;
		istringstream ss(str);
		ss >> num;
		ss >> kth;
		if (num == 0 && kth == 0)
			break;
		if (num == 1) {
			cout << 1 << endl;
			continue;
		}
		struct Person * curr = init();
		struct Person * kill, *burier;
		for (int i = 1; i < num; i++) {
			for (int j = 1; j < kth; j++) {
				curr = curr->next;
			}
			kill = curr;
			kill->pre->next = kill->next;
			kill->next->pre = kill->pre;
			curr = curr->next;
			for (int j = 1; j < kth; j++) {
				curr = curr->next;
			}
			burier = curr;
			//cout << "kill : " << kill->nu << " burier: " << burier->nu << endl;
			if (kill->pre != burier && kill->next != burier) {
				kill->pre->next = burier;
				kill->next->pre = burier;
				burier->next->pre = burier->pre;
				burier->pre->next = burier->next;
				burier->next = kill->next;
				burier->pre = kill->pre;
			}
			delete kill;
			curr = burier->next;
		}
		//cout << "survivor : " << curr->nu << endl;
		int n = num - curr->nu + 2;
		n = (n == num + 1) ? 1 : n;
		cout << n << endl;
		delete curr;
	}
	return 0;
}
