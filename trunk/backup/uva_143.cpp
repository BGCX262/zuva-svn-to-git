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

#define DEBUG 0

#define ZOOMIN 100

/**
 * 0.9999 0.9999 1.0001 0.9999 0.9999 1.0001
 0 0 0 0 0 0

 should return 0
 *
 */

struct Array {
	int x;
	int y;
};
/**
 *    c
 *
 *  a    b
 */
struct Triangle {
	struct Array a;
	struct Array b;
	struct Array c;
};

/**
 * return the direction of what turn
 * >0 : left
 *  0 : straight
 *  <0 : right
 */
int turn(struct Array & p0, struct Array & p1, struct Array & p2) {
	//	cout << "turn " << p0.x << "," << p0.y << " " << p1.x << "," << p1.y << " "
	//			<< p2.x << "," << p2.y << endl;
	//  p0->p1 cross product p0->p2
	// (p1-p0)cross product(p2-p0) = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0)
	int re = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
	//	if (DEBUG) {
	//		cout << "p0:(" << p0.x << "," << p0.y << ") p1:(" << p1.x << "," << p1.y << ", p2:(" << p2.x << "," << p2.y << ") ";
	//		cout << "turn:" << re << endl;
	//	}
	return re;
}

bool isPointInTriangle(struct Triangle & tr, int & x, int & y) {
	if (tr.a.x == x && tr.a.y == y)
		return true;
	if (tr.b.x == x && tr.b.y == y)
		return true;
	if (tr.c.x == x && tr.c.y == y)
		return true;

	struct Array p;
	p.x = x;
	p.y = y;

	if (turn(tr.a, tr.b, p) < 0 || turn(tr.b, tr.c, p) < 0 || turn(tr.c, tr.a, p) < 0)
		return false;

	return true;
}
void sortInAntiClock(struct Array & p0, struct Array & p1, struct Array & p2) {
	int tx;
	int ty;
	if (p0.y > p1.y || (p0.y == p1.y && p0.x > p1.x)) {
		tx = p0.x;
		ty = p0.y;
		p0.x = p1.x;
		p0.y = p1.y;
		p1.x = tx;
		p1.y = ty;
	}
	if (p0.y > p2.y || (p0.y == p2.y && p0.x > p2.x)) {
		tx = p0.x;
		ty = p0.y;
		p0.x = p2.x;
		p0.y = p2.y;
		p2.x = tx;
		p2.y = ty;
	}
	if (turn(p0, p1, p2) < 0) {
		//swap p1 and p2
		tx = p1.x;
		ty = p1.y;
		p1.x = p2.x;
		p1.y = p2.y;
		p2.x = tx;
		p2.y = ty;
	}
}

int min(int & f1, int & f2, int & f3) {
	int min = f1;
	if (f2 < min)
		min = f2;
	if (f3 < min)
		min = f3;
	return min;
}

int max(int & f1, int & f2, int & f3) {
	int max = f1;
	if (f2 > max)
		max = f2;
	if (f3 > max)
		max = f3;
	return max;
}

int main(int argc, char * argv[]) {
	string str;
	float x1, y1, x2, y2, x3, y3;
	vector<struct Array> selections;
	while (true) {
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		cin >> x3;
		cin >> y3;
		if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0)
			break;

		struct Triangle tr;

		tr.a.x = (int)((x1 * ZOOMIN) + 0.5);
		tr.a.y = (int)((y1 * ZOOMIN) + 0.5);
		tr.b.x = (int)((x2 * ZOOMIN) + 0.5);
		tr.b.y = (int)((y2 * ZOOMIN) + 0.5);
		tr.c.x = (int)((x3 * ZOOMIN) + 0.5);
		tr.c.y = (int)((y3 * ZOOMIN) + 0.5);

		//		cin >> tr.a.x;
		//		cin >> tr.a.y;
		//		cin >> tr.b.x;
		//		cin >> tr.b.y;
		//		cin >> tr.c.x;
		//		cin >> tr.c.y;

		//		if (tr.a.x == 0 && tr.a.y == 0 && tr.b.x == 0 && tr.b.y == 0 && tr.c.x
		//				== 0 && tr.c.y == 0) {
		//			break;
		//		}

		sortInAntiClock(tr.a, tr.b, tr.c);
		int left = min(tr.a.x, tr.b.x, tr.c.x);
		if (left % ZOOMIN != 0)
			left = (left / ZOOMIN + 1) * ZOOMIN;
		int right = max(tr.a.x, tr.b.x, tr.c.x);
		if (right % ZOOMIN != 0)
			right = right / ZOOMIN * ZOOMIN;
		int high = max(tr.a.y, tr.b.y, tr.c.y);
		if (high % ZOOMIN != 0)
			high = high / ZOOMIN * ZOOMIN;
		int low = min(tr.a.y, tr.b.y, tr.c.y);
		if (low % ZOOMIN != 0)
			low = (low / ZOOMIN + 1) * ZOOMIN;
		if (left < ZOOMIN)
			left = ZOOMIN;
		if (low < ZOOMIN)
			low = ZOOMIN;
		if (right > 99 * ZOOMIN)
			right = 99 * ZOOMIN;
		if (high > 99 * ZOOMIN)
			high = 99 * ZOOMIN;

		//		int left = ceil(min(tr.a.x, tr.b.x, tr.c.x));
		//		int right = floor(max(tr.a.x, tr.b.x, tr.c.x));
		//		int high = floor(max(tr.a.y, tr.b.y, tr.c.y));
		//		int low = ceil(min(tr.a.y, tr.b.y, tr.c.y));
		//		if (left < 1)
		//			left = 1;
		//		if (low < 1)
		//			low = 1;
		//		if (right > 99)
		//			right = 99;
		//		if (high > 99)
		//			high = 99;

		if (DEBUG) {
			cout << "a(" << tr.a.x << "," << tr.a.y << ") b(" << tr.b.x << "," << tr.b.y << ") c(" << tr.c.x << "," << tr.c.y << ")" << endl;
			cout << "left: " << left << ", right :" << right << ", high:" << high << ", low:" << low << endl;
		}
		int counter = 0;
		for (int i = left; i <= right; i = i + ZOOMIN) {
			for (int j = low; j <= high; j = j + ZOOMIN) {
				if (isPointInTriangle(tr, i, j))
					counter++;
			}
		}
		//		for (int i = left; i <= right; i++) {
		//			for (int j = low; j <= high; j++) {
		//				if (isPointInTriangle(tr, i, j))
		//					counter++;
		//			}
		//		}

		cout << setw(4) << counter << endl;
	}

	return 0;
}
