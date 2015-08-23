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
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG 1

struct Array {
	int x;
	int y;
	bool visible;
	Point() {
		visible = true;
	}
};

struct Region {
	struct Array topLeft;
	struct Array bottomRight;
};

bool isPointInRegion(struct Region & re, struct Array & p) {
	if (p.x >= re.topLeft.x && p.x <= re.bottomRight.x && p.y >= re.topLeft.y && p.y <= re.bottomRight.y)
		return true;
	return false;
}

double distanceBetweenPoins(struct Array & p1, struct Array & p2) {
	return sqrt(double((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

int main(int argc, char * argv[]) {
	string str;
	int x1, y1, x2, y2;
	vector<struct Array> icons;
	vector<struct Region> regions;
	vector<string> selections;
	bool filterVisible = false;
	while (cin >> str) {
		if (str == "#") {
			break;
		}
		if (str == "I") {
			struct Array p;
			cin >> p.x;
			cin >> p.y;
			icons.push_back(p);
		} else if (str == "R") {
			struct Region re;
			cin >> re.topLeft.x;
			cin >> re.topLeft.y;
			cin >> re.bottomRight.x;
			cin >> re.bottomRight.y;
			regions.push_back(re);
		} else if (str == "M") {
			if (!filterVisible) {
				filterVisible = true;
				for (int i = 0; i < regions.size(); i++) {
					for (int j = 0; j < icons.size(); j++) {
						if (icons[j].visible && isPointInRegion(regions[i], icons[j])) {
							icons[j].visible = false;
						}
					}
				}
			}
			struct Array mouseClick;
			cin >> mouseClick.x;
			cin >> mouseClick.y;
			bool select = false;
			for (int i = regions.size() - 1; i >= 0; i--) {
				if (isPointInRegion(regions[i], mouseClick)) {
					cout << char('A' + i) << endl;
					select = true;
					break;
				}
			}
			if (!select) {
				vector<int> selectIcons;
				double minDistance;
				for (int i = 0; i < icons.size(); i++) {
					if (icons[i].visible) {
						double dis = distanceBetweenPoins(icons[i], mouseClick);
						if (selectIcons.size() == 0) {
							minDistance = dis;
							selectIcons.push_back(i + 1);
							continue;
						}
						if (dis < minDistance) {
//							if (DEBUG) {
//								cout << "distance:" << dis << " less than minDistance:" << minDistance << endl;
//							}
							selectIcons.clear();
							selectIcons.push_back(i + 1);
							minDistance = dis;
						} else if (dis == minDistance) {
							selectIcons.push_back(i + 1);
						}
					}
				}
				for (int i = 0; i < selectIcons.size(); i++) {
					cout << setw(3) << selectIcons[i];
				}
				cout << endl;
			}
		}
	}
	return 0;
}
