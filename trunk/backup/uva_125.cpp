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

#define DEBUG 0

/**
 * the second solution could only solve situiation
 * where there is only one way between intersections
 * there maybe some input like this:
 *
 *
 input:
 4
 1 2
 1 2
 1 2
 2 3
 2 3
 output:
 0 0 0 0
 0 0 3 6
 0 0 0 2
 0 0 0 0
 */

int main(int argc, char * argv[]) {
	int maxV = 0;
	int c[30][30];
	int numEdg, a, b, cityOrder = -1;
	while (cin >> numEdg) {
		cityOrder++;
		maxV = 0;
		memset(c, 0, sizeof(c));
		for (int i = 0; i < numEdg; i++) {
			cin >> a >> b;
			if (a > maxV)
				maxV = a;
			if (b > maxV)
				maxV = b;
			c[a][b]++;
		}
		for (int k = 0; k <= maxV; k++) {
			for (int i = 0; i <= maxV; i++) {
				for (int j = 0; j <= maxV; j++) {
					c[i][j] = c[i][j] + (c[i][k] * c[k][j]);
				}
			}
		}
		for (int k = 0; k <= maxV; k++) {
			if (c[k][k] > 0) {
				c[k][k] = -1;
				for (int i = 0; i <= maxV; i++) {
					for (int j = 0; j <= maxV; j++) {
						if (c[i][k] != 0 && c[k][j] != 0) {
							c[i][j] = -1;
						}
					}
				}
			}
		}

		cout << "matrix for city " << cityOrder << endl;
		if (numEdg > 0) {
			for (int i = 0; i <= maxV; i++) {
				for (int j = 0; j <= maxV; j++) {
					if (j > 0) {
						cout << " ";
					}
					cout << c[i][j];
				}
				cout << endl;
			}
		}
	}
	return 0;
}

/*
 struct Vertex {
 bool visited;
 bool cycle;
 map<int, int> out;
 int dfsnum;
 int low;
 };
 static int maxNode = 0;
 static int counter[30][30];
 static struct Vertex * vert[31];

 void printV(int i) {
 cout << "vert:" << i;
 cout << ",low:" << vert[i]->low << ", dfsnum:" << vert[i]->dfsnum;
 cout << ",visited:" << vert[i]->visited;
 cout << ",cycle:" << vert[i]->cycle;
 cout << endl;
 }

 struct Vertex * alloc() {
 struct Vertex * p = new struct Vertex;
 p->cycle = false;
 p->visited = false;
 p->dfsnum = 0;
 p->low = 0;
 return p;
 }

 void init() {
 maxNode = 0;
 memset(counter, 0, sizeof(counter));
 for (int i = 0; i < 31; i++) {
 if (vert[i] != NULL) {
 delete vert[i];
 vert[i] = NULL;
 }
 }
 }

 void connect(int a, int b) {
 if (a == b)
 return;
 if (vert[a] == NULL) {
 vert[a] = alloc();
 }
 map<int, int>::iterator itr = vert[a]->out.find(b);
 if (itr == vert[a]->out.end()) {
 vert[a]->out[b] = 1;
 } else {
 vert[a]->out[b]++;
 }
 if (vert[b] == NULL) {
 vert[b] = alloc();
 }
 }

 bool find(vector<int> & stack, int v) {
 int size = stack.size();
 for (int i = 0; i < size; i++) {
 if (stack[i] == v)
 return true;
 }
 return false;
 }

 void tarjan_dfs(int v, vector<int> & stack, int & dfsMax) {
 vert[v]->visited = true;
 stack.push_back(v);
 vert[v]->dfsnum = dfsMax;
 vert[v]->low = dfsMax;
 dfsMax++;
 for (map<int, int>::iterator i = vert[v]->out.begin(); i != vert[v]->out.end(); i++) {
 int w = i->first;
 if (vert[w]->visited == false) {
 tarjan_dfs(w, stack, dfsMax);
 vert[v]->low = vert[v]->low < vert[w]->low ? vert[v]->low : vert[w]->low;
 } else if (find(stack, w)) {
 vert[v]->low = vert[v]->low < vert[w]->dfsnum ? vert[v]->low : vert[w]->dfsnum;
 }
 }
 if (vert[v]->low == vert[v]->dfsnum) {
 int w = stack.back();
 stack.pop_back();
 if (w == v) {
 return;
 }
 while (w != v) {
 vert[w]->cycle = true;
 w = stack.back();
 stack.pop_back();
 }
 vert[w]->cycle = true;
 }
 }

 void findCycle() {
 vector<int> stack;
 int dfsMax = 0;
 for (int i = 0; i <= maxNode; i++) {
 if (vert[i] != NULL) {
 connect(30, i);
 }
 }
 tarjan_dfs(30, stack, dfsMax);
 }

 void dfs(int from, int a) {
 for (map<int, int>::iterator i = vert[a]->out.begin(); i != vert[a]->out.end(); i++) {
 int w = i->first;
 if (counter[from][w] == -1)
 continue;
 if (vert[from]->cycle || vert[w]->cycle || vert[a]->cycle || counter[from][a] == -1) {
 counter[from][w] = -1;
 } else {
 counter[from][w] = counter[from][a] + i->second;
 }

 dfs(from, w);
 }
 }

 void buildMatrix() {
 for (int i = 0; i <= maxNode; i++) {
 if (vert[i] != NULL) {
 dfs(i, i);
 }
 }
 }

 int main(int argc, char * argv[]) {
 string str, aStr, bStr;
 int numEdg, a, b, cityOrder = -1;
 while (cin >> str) {
 cityOrder++;
 init();
 istringstream(str) >> numEdg;
 maxNode = 0;
 for (int i = 0; i < numEdg; i++) {
 cin >> aStr;
 istringstream(aStr) >> a;
 cin >> bStr;
 istringstream(bStr) >> b;
 if (a > maxNode)
 maxNode = a;
 if (b > maxNode)
 maxNode = b;
 connect(a, b);
 }
 for (int i = 0; i <= maxNode; i++) {
 if (vert[i] == NULL) {
 vert[i] = alloc();
 }
 }
 findCycle();
 buildMatrix();
 cout << "matrix for city " << cityOrder << endl;
 if (numEdg > 0) {
 for (int i = 0; i <= maxNode; i++) {
 for (int j = 0; j <= maxNode; j++) {
 if (j > 0) {
 cout << " ";
 }
 cout << counter[i][j];
 }
 cout << endl;
 }
 }
 }
 return 0;
 }
 */
