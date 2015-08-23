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

struct Term {
	int coeff;
	int xExpo;
	int yExpo;
};

vector<struct Term *> v1, v2, v3;

void printV(vector<struct Term *> & v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i]->coeff << "x" << v[i]->xExpo << "y" << v[i]->yExpo << " ";
	}
	cout << endl;
}

struct Term * alloc() {
	struct Term * p = new struct Term;
	p->coeff = 0;
	p->xExpo = 0;
	p->yExpo = 0;
	return p;
}

void init() {
	int len = v1.size();
	for (int i = 0; i < len; i++) {
		delete v1[i];
	}
	v1.clear();
	len = v2.size();
	for (int i = 0; i < len; i++) {
		delete v2[i];
	}
	v2.clear();
	len = v3.size();
	for (int i = 0; i < len; i++) {
		delete v3[i];
	}
	v3.clear();
}

void setTerm(string & str, vector<struct Term *> &v) {
	if (DEBUG) {
		cout << "setTerm " << str << endl;
	}
	struct Term * t = alloc();
	int fX = str.find("x");
	int fY = str.find("y");
	/**
	 * set coefficient
	 */
	int fLeft = (fX <= fY ? fX : fY);
	int fRight = (fX >= fY ? fX : fY);
	if (str[0] == '-' && (fLeft == 1 || fRight == 1)) {
		t->coeff = -1;
	} else if (fLeft == 0 || fRight == 0) {
		t->coeff = 1;
	} else if (fLeft == string::npos && fRight == string::npos) {
		istringstream(str) >> t->coeff;
	} else if (fLeft == string::npos && fRight != string::npos) {
		istringstream(str.substr(0, fRight)) >> t->coeff;
	} else if (fLeft != string::npos && fRight != string::npos) {
		istringstream(str.substr(0, fLeft)) >> t->coeff;
	}

	/**
	 * set fLeft 's exponential
	 */
	int leftExpo = 0;
	if (fLeft == string::npos) {
		leftExpo = 0;
	} else if (fLeft == fRight - 1) {
		leftExpo = 1;
	} else if (fLeft >= 0 && fLeft < fRight - 1) {
		istringstream(str.substr(fLeft + 1, fRight - fLeft - 1)) >> leftExpo;
	}
	/**
	 * set fRight's exponential
	 */
	int rightExpo = 0;
	if (fRight == string::npos) {
		rightExpo = 0;
	} else if (fRight == str.size() - 1) {
		rightExpo = 1;
	} else if (fRight < str.size() - 1) {
		istringstream(str.substr(fRight + 1, str.size() - fRight - 1)) >> rightExpo;
	}
	if (fLeft == fX) {
		t->xExpo = leftExpo;
		t->yExpo = rightExpo;
	} else {
		t->xExpo = rightExpo;
		t->yExpo = leftExpo;
	}
	v.push_back(t);
}

void setPolynomials(string & str, vector<struct Term *> &v) {
	istringstream issPlus(str);
	string str1, str2;
	while (getline(issPlus, str1, '+')) {
		if (str1.find('-') != string::npos) {
			istringstream issMin(str1);
			bool firstChar = true;
			while (getline(issMin, str2, '-')) {
				if (str2.size() > 0) {
					if (str1[0] != '-' && firstChar) {
						firstChar = false;
					} else {
						str2.insert(0, "-");
					}
					setTerm(str2, v);
				}
			}
		} else {
			setTerm(str1, v);
		}
	}
}

void insertToV3(int co, int xE, int yE) {
	if (DEBUG) {
		cout << "insert " << co << "," << xE << "," << yE << endl;
	}
	for (vector<struct Term*>::iterator i = v3.begin(); i != v3.end(); i++) {
		if ((*i)->xExpo < xE || ((*i)->xExpo == xE && (*i)->yExpo > yE)) {
			struct Term * v = alloc();
			v->coeff = co;
			v->xExpo = xE;
			v->yExpo = yE;
			v3.insert(i, v);
			return;
		} else if ((*i)->xExpo == xE && (*i)->yExpo == yE) {
			(*i)->coeff += co;
			return;
		}
	}
	struct Term * v = alloc();
	v->coeff = co;
	v->xExpo = xE;
	v->yExpo = yE;
	v3.push_back(v);
}

void multiply() {
	int co, xE, yE;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			co = v1[i]->coeff * v2[j]->coeff;
			xE = v1[i]->xExpo + v2[j]->xExpo;
			yE = v1[i]->yExpo + v2[j]->yExpo;
			insertToV3(co, xE, yE);
		}
	}
}

void printV3Terms() {
	string l1, l2;
	bool first = true;
	for (int i = 0; i < v3.size(); i++) {
		if (v3[i]->coeff == 0) {
			continue;
		}
		string s1 = "", s2 = "";
		if (first) {
			if (v3[i]->coeff < 0) {
				s1 += " ";
				s2 += "-";
			}
			first = false;
		} else {
			if (v3[i]->coeff < 0) {
				s1 += "   ";
				s2 += " - ";
			} else {
				s1 += "   ";
				s2 += " + ";
			}
		}

		if ((v3[i]->coeff != -1 && v3[i]->coeff != 1) || (v3[i]->xExpo == 0 && v3[i]->yExpo == 0)) {
			stringstream ss;
			ss << (v3[i]->coeff > 0 ? v3[i]->coeff : 0 - v3[i]->coeff);
			s2 += ss.str();
			for (int j = 0; j < ss.str().size(); j++) {
				s1 += " ";
			}
		}

		if (v3[i]->xExpo != 0) {
			s1 += " ";
			s2 += "x";
			if (v3[i]->xExpo != 1) {
				stringstream ss;
				ss << v3[i]->xExpo;
				s1 += ss.str();
				for (int j = 0; j < ss.str().size(); j++) {
					s2 += " ";
				}
			}
		}
		if (v3[i]->yExpo != 0) {
			s1 += " ";
			s2 += "y";
			if (v3[i]->yExpo != 1) {
				stringstream ss;
				ss << v3[i]->yExpo;
				s1 += ss.str();
				for (int j = 0; j < ss.str().size(); j++) {
					s2 += " ";
				}
			}
		}
		//cout << "s1:" << s1 << endl;
		//cout << "s2:" << s2 << endl;
		l1 += s1;
		l2 += s2;
	}
	cout << l1 << endl;
	cout << l2 << endl;
}

int main(int argc, char * argv[]) {
	string str1, str2;
	while (cin >> str1) {
		if (str1.compare("#") == 0)
			break;
		cin >> str2;
		init();
		setPolynomials(str1, v1);
		setPolynomials(str2, v2);
		if (DEBUG) {
			printV(v1);
			printV(v2);
		}
		multiply();
		if (DEBUG) {
			printV(v3);
		}
		printV3Terms();
	}
	return 0;
}
