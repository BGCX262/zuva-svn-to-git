#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;
//If (x1,y1) are the coordinates of the vertex for which you want the angle
//find the slope of the sides of the angle first:
//(y2 -y1)/(x2-x1) =m2 (the slope of the line drawn to point 2)
//(Y3-y1)/(x2-x1) m3 (the slope of the line drawn to point 3)
//The tangent of the angle at point one is:
//tan Θ = (m3-m2)/(1+m3*m2)

//#include <math.h>
//
//#define PI 3.14159265
//
//int main ()
//{
//  double param, result;
//  param = 1.0;
//  result = atan (param) * 180 / PI;
//  printf ("The arc tangent of %lf is %lf degrees\n", param, result );
//  return 0;
//}

//return11
//20 10
//15 3 12 5 16 6 13 7 17 9 10 14 12 8 7 9 11 8 9 6 12 1 0 0
//return5
//2 2
//1 1  3 1  3 3  1 3  2 1  3 2  2 3  1 2  0 0
//UZJWU2
//9 15
//1 7 6 2 9 14 13 17 18 9 23 29 24 5 25 12 28 7 32 18 37 17 41 27 46 3 49 29 53 29 54 10 58 29 63 25 63 56 58 43 54 25 53 34 49 51 46 23 41 50 37 38 32 26 28 30 25 42 24 24 23 34 18 35 13 46 9 43 6 14 0 0
//YVTJTOOO17
//49 2
//1 2 5 7 10 30 14 22 15 4 17 6 20 24 23 22 24 1 27 22 31 6 35 21 36 17 39 30 43 20 45 20 49 1 52 10 57 30 61 2 66 26 68 26 71 18 73 11 74 8 76 9 77 13 81 22 86 15 90 6 90 30 86 41 81 53 77 43 76 30 74 35 73 23 71 35 68 37 66 55 61 10 57 48 52 16 49 7 45 37 43 48 39 41 36 28 35 23 31 10 27 51 24 23 23 40 20 53 17 28 15 13 14 51 10 32 5 37 0 0

#define PI 3.14159265
#define DEBUG 0

struct Array {
	int x;
	int y;
	int num;
	bool isOnEdge;
	float angle;
};

bool compareByAngle(const struct Array & p1, const struct Array & p2) {
	if (p1.angle < p2.angle) {
		return true;
	} else if (p1.angle > p2.angle) {
		return false;
	} else {
		if (p1.x < p2.x) {
			return true;
		} else if (p1.x > p2.x) {
			return false;
		} else {
			if (p1.y > p2.y) {
				return true;
				//return false;
			} else if (p1.y < p2.y) {
				return false;
				//return true;
			} else {
				return true;
			}
		}
	}
}

float calAngle3(struct Array & p1, struct Array & p2, struct Array & p3) {
	/**
	 * http://en.wikipedia.org/wiki/Triangle
	 * p1--(b)--->p2----(c)--->p3--(a)--->p1
	 * angle of p2 is arccos( ( b^2 + c^2 - a^2)/ 2*b*c)
	 * degree of angle = redians * 180 / PI
	 * 90 degree = (PI/2) * 180 / PI
	 */
	float b2 = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
	float c2 = pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2);
	float a2 = pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2);
	float re = acos((b2 + c2 - a2) / (2 * sqrt(b2) * sqrt(c2))) * 180 / PI;
	if (DEBUG) {
		cout << "calAngle3 " << p1.x << "," << p1.y << " to " << p2.x << "," << p2.y << " to " << p3.x << "," << p3.y << " re:" << re << endl;
	}
	return re;
}

float calAngle2(struct Array & p1, struct Array & p2) {
	/**
	 * redians of angle = atan((y2-y1/x2-x1))
	 * degree of angle = redians * 180 / PI
	 */
	return atan2(p2.y - p1.y, p2.x - p1.x);
}

/**
 * return the direction of what turn
 * 1 : left
 *  0 : straight
 *  -1 : right
 */
int turn(struct Array & p0, struct Array & p1, struct Array & p2) {
	//	cout << "turn " << p0.x << "," << p0.y << " " << p1.x << "," << p1.y << " "
	//			<< p2.x << "," << p2.y << endl;

	//  p0->p1 cross product p0->p2
	// (p1-p0)cross product(p2-p0) = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0)
	int r = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
	if (r > 0)
		return 1;
	else if (r < 0)
		return -1;
	else
		return 0;
}

void calConvexHull(vector<struct Array> & v) {
	// using graham-scan algorithm to find convex hull
	int min = 0;
	int vSize = v.size();
	for (int i = 1; i < vSize; i++) {
		if (v[i].y < v[min].y || (v[i].y == v[min].y && v[i].x < v[min].x)) {
			min = i;
		}
	}
	struct Array temp = v[0];
	v[0] = v[min];
	v[min] = temp;

	//	cout << "v[0]:" << v[0].x << "," << v[0].y << endl;

	for (int i = 0; i < v.size(); i++) {

		v[i].angle = calAngle2(v[0], v[i]);

	}

	//	cout << "v before..." << endl;
	//	for (int i = 0; i < v.size(); i++) {
	//		cout << v[i].x << "," << v[i].y << " num:" << v[i].num << " angle:"
	//				<< v[i].angle << endl;
	//	}

	sort(v.begin(), v.end(), &compareByAngle);

	if (DEBUG) {
		cout << "v after..." << endl;
		for (int i = 0; i < v.size(); i++) {
			cout << v[i].x << "," << v[i].y << " num:" << v[i].num << " angle:" << v[i].angle << endl;
		}
	}

	if (turn(v[0], v[1], v[2]) == 0) {
		if (v[1].y < v[2].y) {
			v[1].isOnEdge = true;
		} else if (v[1].y == v[2].y) {
			if (v[1].x < v[2].x) {
				v[1].isOnEdge = true;
			} else {
				v[2].isOnEdge = true;
			}
		} else {
			v[2].isOnEdge = true;
		}
	}

	stack<struct Array> s;
	s.push(v[0]);
	s.push(v[1]);
	s.push(v[2]);

	for (int i = 3; i < vSize; i++) {
		while (true) {

			struct Array top = s.top();
			s.pop();

			if (s.empty()) {
				s.push(top);
				s.push(v[i]);
				break;
			}

			struct Array nextTop = s.top();
			int t = turn(nextTop, top, v[i]);
			if (t == -1) {
				continue;
			} else if (t == 0) {
				if (top.y < v[i].y) {
					top.isOnEdge = true;
				} else if (top.y == v[i].y) {
					if (top.x < v[i].x) {
						top.isOnEdge = true;
					} else {
						v[i].isOnEdge = true;
					}
				} else {
					v[i].isOnEdge = true;
				}
				s.push(top);
				s.push(v[i]);
				//				cout << "push:" << top.x << "," << top.y << " " << v[i].x
				//						<< "," << v[i].y << endl;
				break;
			} else {
				s.push(top);
				s.push(v[i]);
				//				cout << "push:" << top.x << "," << top.y << " " << v[i].x
				//						<< "," << v[i].y << endl;
				break;
			}
		}
	}

	v.clear();
	while (!s.empty()) {
		v.insert(v.begin(), s.top());
		//v.push_back(s.top());
		s.pop();
	}
}

bool isStable(struct Array & center, struct Array & p1, struct Array & p2) {
	//float pi2 = PI / 2;
	float pi2 = 90;
	float a1 = calAngle3(p1, p2, center);
	float a2 = calAngle3(p2, p1, center);
	if (DEBUG && a1 < pi2 && a1 > 0 && a2 < pi2 && a2 > 0)
		cout << "isStable, center:" << center.x << "," << center.y << " " << p1.x << "," << p1.y << " " << p2.x << "," << p2.y << " a1:" << a1 << ",a2:" << a2
				<< endl;
	return a1 <= pi2 && a1 >= 0 && a2 <= pi2 && a2 >= 0;
}

int calMinNum(struct Array & center, vector<struct Array> & v) {
	int vSize = v.size();
	if (DEBUG) {
		cout << "v in calMinNum..." << endl;
		for (int i = 0; i < v.size(); i++) {
			cout << v[i].x << "," << v[i].y << " num:" << v[i].num << " isOnEdge:" << v[i].isOnEdge << endl;
		}

	}
	int left = -1;
	int minNum = -1;
	for (int i = 0; i < vSize; i++) {
		if (!v[i].isOnEdge && left == -1) {
			left = i;
			continue;
		}
		if (!v[i].isOnEdge && left != -1) {
			if (isStable(center, v[left], v[i])) {
				int maxNum = v[left].num;
				for (int j = left + 1; j <= i; j++) {
					if (v[j].num > maxNum) {
						maxNum = v[j].num;
					}
				}
				if (minNum == -1 || maxNum < minNum) {
					minNum = maxNum;
					//cout << "minNum:" << minNum << endl;
				}

			}
			left = i;
		}
	}

	for (int i = 0; i < vSize; i++) {
		if (!v[i].isOnEdge) {
			if (isStable(center, v[left], v[i])) {
				int maxNum = v[left].num;
				for (int j = left + 1; j < vSize; j++) {
					if (v[j].num > maxNum) {
						maxNum = v[j].num;
					}
				}
				for (int j = 0; j <= i; j++) {
					if (v[j].num > maxNum) {
						maxNum = v[j].num;
					}
				}
				if (minNum == -1 || maxNum < minNum) {
					minNum = maxNum;
					//cout << "minNum:" << minNum << endl;
				}
			}

			break;
		}

	}

	return minNum;
}

int main(int argc, char * argv[]) {
	string str1;
	while (getline(cin, str1)) {
		if (str1 == "#")
			break;
		string str2, str3;
		struct Array center;
		getline(cin, str2);
		istringstream ss2(str2);
		ss2 >> center.x;
		ss2 >> center.y;
		getline(cin, str3);
		istringstream ss3(str3);
		vector<struct Array> v;
		int num = 1;
		while (true) {
			struct Array p;
			ss3 >> p.x;
			ss3 >> p.y;
			p.isOnEdge = false;
			if (p.x == 0 && p.y == 0) {
				// calculate
				calConvexHull(v);
				cout << str1;
				for (int i = str1.size(); i < 20; ++i)
					cout << " ";
				cout << calMinNum(center, v) << endl;
				break;
			} else {
				p.num = num++;
				bool already = false;
				for (int i = 0; i < v.size(); i++) {
					if (v[i].x == p.x && v[i].y == p.y) {
						v[i].num = p.num;
						already = true;
					}
				}
				if (!already)
					v.push_back(p);
			}
		}
	}
	return 0;
}
