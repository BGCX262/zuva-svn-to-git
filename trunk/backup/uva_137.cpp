#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>
//#include <iomanip>
#include <cstdio>
#include <cassert>

using namespace std;

#define DEBUG 0

struct Array {
	float x;
	float y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point() {
		this->x = 0;
		this->y = 0;
	}
};

float calArea(vector<struct Array>& p) {
	float re = 0;
	int size = p.size();
	if (size == 0)
		return 0;
	for (int i = 0; i < size - 1; i++) {
		re += (p[i].x * p[i + 1].y - p[i + 1].x * p[i].y);
	}
	re += (p[size - 1].x * p[0].y - p[0].x * p[size - 1].y);
	re /= 2;
	re = abs(re);
	//	if (DEBUG) {
	//		for (int i = 0; i < p.size(); i++) {
	//			cout << p[i].x << "," << p[i].y << " ";
	//		}
	//		cout << endl;
	//		cout << "area:" << re << endl;
	//	}

	return re;
}

struct Array intersection(struct Array & p1, struct Array & p2, struct Array & p3, struct Array & p4) {
	struct Array inter;
	float x = (p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x);
	x /= (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	float y = (p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x);
	y /= (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	inter.x = x;
	inter.y = y;
	if (DEBUG) {
		cout << "(" << p1.x << "," << p1.y << ") to (" << p2.x << "," << p2.y << ")" << " and " << "(" << p3.x << "," << p3.y << ") to (" << p4.x << ","
				<< p4.y << ")" << " has intersection (" << inter.x << "," << inter.y << ")" << endl;
	}
	return inter;
}

bool isInside(struct Array & p0, struct Array & p1, struct Array & p2) {
	return (((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y)) <= 0) ? true : false;
}
void clipPolygon(vector<struct Array>& subjectPolygon, vector<struct Array> & clipPolygon, vector<struct Array>& outputList) {
	//Sutherland–Hodgman algorithm
	//	List outputList = subjectPolygon;
	//	  for (Edge clipEdge in clipPolygon) do
	//	     List inputList = outputList;
	//	     outputList.clear();
	//	     Point S = inputList.last;
	//	     for (Point E in inputList) do
	//	        if (E inside clipEdge) then
	//	           if (S not inside clipEdge) then
	//	              outputList.add(ComputeIntersection(S,E,clipEdge));
	//	           end if
	//	           outputList.add(E);
	//	        else if (S inside clipEdge) then
	//	           outputList.add(ComputeIntersection(S,E,clipEdge));
	//	        end if
	//	        S = E;
	//	     done
	//	  done
	for (int i = 0; i < subjectPolygon.size(); i++) {
		outputList.push_back(subjectPolygon[i]);
	}

	for (int i = 0; i < clipPolygon.size(); i++) {
		// edge is p0 -> p1
		struct Array edge0 = clipPolygon[i];
		struct Array edge1;
		if (i == clipPolygon.size() - 1)
			edge1 = clipPolygon[0];
		else
			edge1 = clipPolygon[i + 1];

		if (DEBUG) {
			cout << "clip edge: (" << edge0.x << "," << edge0.y << ") to (" << edge1.x << "," << edge1.y << ")" << endl;
		}

		if (outputList.size() == 0)
			return;

		vector<struct Array> inputList;
		for (int j = 0; j < outputList.size(); j++) {
			inputList.push_back(outputList[j]);
		}
		outputList.clear();
		if (DEBUG) {
			cout << "inputList:" << endl;
			for (int j = 0; j < inputList.size(); j++) {
				cout << "(" << inputList[j].x << "," << inputList[j].y << ") ";
			}
			cout << endl;
		}

		struct Array s = inputList[inputList.size() - 1];
		struct Array e;

		for (int j = 0; j < inputList.size(); j++) {
			e = inputList[j];

			if (DEBUG) {
				cout << "s : (" << s.x << "," << s.y << ") e : (" << e.x << "," << e.y << ")" << endl;
			}

			if (isInside(edge0, edge1, e)) {
				if (!isInside(edge0, edge1, s)) {
					//add intersection of s, e and edge
					outputList.push_back(intersection(edge0, edge1, e, s));
				}
				outputList.push_back(e);
			} else if (isInside(edge0, edge1, s)) {
				//add intersection of s, e and edge
				outputList.push_back(intersection(edge0, edge1, s, e));
			}
			s = e;
		}
	}
}

float calExclusiveOverlapArea(vector<struct Array>& p1, vector<struct Array> & p2) {
	if (DEBUG) {
		cout << "p1 which is the subject:" << endl;
		for (int i = 0; i < p1.size(); i++) {
			cout << "(" << p1[i].x << "," << p1[i].y << ") ";
		}
		cout << endl;

		cout << "p2 which is the clip polygon:" << endl;
		for (int i = 0; i < p2.size(); i++) {
			cout << "(" << p2[i].x << "," << p2[i].y << ") ";
		}
		cout << endl;
	}
	if (p1.size() == p2.size()) {
		bool match = true;
		for (int i = 0; i < p1.size(); i++) {
			if (p1[i].x != p2[i].x || p1[i].y != p2[i].y) {
				match = false;
				break;
			}
		}
		if (match)
			return 0;
	}

	float a1 = calArea(p1);
	float a2 = calArea(p2);

	vector<struct Array> p3;
	clipPolygon(p1, p2, p3);

	float a3 = calArea(p3);

	if (DEBUG) {
		cout << "p3 which is the overlap polygon:" << endl;
		for (int i = 0; i < p3.size(); i++) {
			cout << "(" << p3[i].x << "," << p3[i].y << ") ";
		}
		cout << endl;
		cout << "a1:" << a1 << ", a2:" << a2 << ", a3:" << a3 << endl;
	}
	return (a1 + a2 - 2 * a3);
}

int main(int argc, char * argv[]) {
	string str1;
	int n, x, y;
	vector<float> areas;
	while (getline(cin, str1)) {
		istringstream ss1(str1);
		ss1 >> n;
		if (n == 0) {
			// print areas
			break;
		}
		vector<struct Array> polygon1, polygon2;
		for (int i = 0; i < n; i++) {
			ss1 >> x;
			ss1 >> y;
			polygon1 .push_back(Array(x, y));
		}
		string str2;
		getline(cin, str2);
		istringstream ss2(str2);
		ss2 >> n;
		for (int i = 0; i < n; i++) {
			ss2 >> x;
			ss2 >> y;
			polygon2 .push_back(Array(x, y));
		}
		areas.push_back(calExclusiveOverlapArea(polygon1, polygon2));
	}

	for (int i = 0; i < areas.size(); i++) {
		printf("%8.2f", areas[i]);
		//		cout << setprecision(3);
		//		cout << setw(8);
		//		cout << areas[i];
	}
	cout << endl;
	return 0;
}
