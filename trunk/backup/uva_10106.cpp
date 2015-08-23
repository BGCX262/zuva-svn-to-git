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

void add(string & s1, string & s2, string & r) {
	int i, j, borrow = 0;
	string result;

	for (i = s1.length() - 1, j = s2.length() - 1; i >= 0 && j >= 0; i--, j--) {
		int n1, n2;
		string nstr;
		istringstream(s1.substr(i, 1)) >> n1;
		istringstream(s2.substr(j, 1)) >> n2;
		int sum = n1 + n2 + borrow;
		borrow = (sum) / 10;
		stringstream ss;
		ss << (sum % 10);
		ss >> nstr;
		result.append(nstr);
	}

	if (i >= 0) {
		for (; i >= 0; i--) {
			int n1, n2 = 0;
			string nstr;
			istringstream(s1.substr(i, 1)) >> n1;
			int sum = n1 + n2 + borrow;
			borrow = (sum) / 10;
			stringstream ss;
			ss << (sum % 10);
			ss >> nstr;
			result.append(nstr);
		}
	}
	if (j >= 0) {
		for (; j >= 0; j--) {
			int n1 = 0, n2;
			string nstr;
			istringstream(s2.substr(j, 1)) >> n2;
			int sum = n1 + n2 + borrow;
			borrow = (sum) / 10;
			stringstream ss;
			ss << (sum % 10);
			ss >> nstr;
			result.append(nstr);
		}
	}
	if (borrow > 0) {
		stringstream ss;
		ss << borrow;
		string nstr;
		ss >> nstr;
		result.append(nstr);
	}
	r.clear();
	r.assign(result.rbegin(), result.rend());

	if (DEBUG) {
		cout << "add, s1:" << s1 << ",s2:" << s2 << ", result:" << r << endl;
	}
}

void multiply10(string & s, int n) {
	if (DEBUG) {
		cout << "multiply10, s:" << s << ", n:" << n << endl;
	}
	if (s == "0")
		return;
	for (int i = 0; i < n; i++) {
		s.insert(s.length(), "0");
	}
	if (DEBUG) {
		cout << "multiply10, s:" << s << endl;
	}
}

void multiply(string & s1, string & s2, string & result) {
	if (DEBUG) {
		cout << "multiply s1:" << s1 << ",s2:" << s2 << endl;
	}
	//base case
	if (s1.length() == 0 || s2.length() == 0) {
		result.clear();
		result.append("0");
		return;
	}
	if (s1.length() <= 2 && s2.length() <= 2) {
		result.clear();
		int n1, n2, resultN;
		istringstream(s1) >> n1;
		istringstream(s2) >> n2;
		stringstream ss;
		ss << (n1 * n2);
		ss >> result;
		if (DEBUG) {
			cout << "s1:" << s1 << ",s2:" << s2 << ",result:" << result << endl;
		}
		return;
	}

	int m = s1.length();
	int n = s2.length();
	string a = s1.substr(0, m / 2);
	string b = s1.substr(m / 2, s1.length() - m / 2);
	string c = s2.substr(0, n / 2);
	string d = s2.substr(n / 2, s2.length() - n / 2);
	if (DEBUG) {
		cout << "a:" << a << ", b:" << b << ", c:" << c << ", d:" << d << endl;
	}

	string ac;
	multiply(a, c, ac);
	multiply10(ac, m - m / 2 + n - n / 2);
	string ad;
	multiply(a, d, ad);
	multiply10(ad, (m - m / 2));
	string bc;
	multiply(b, c, bc);
	multiply10(bc, (n - n / 2));
	string bd;
	multiply(b, d, bd);

	string acad;
	add(ac, ad, acad);
	string bcbd;
	add(bc, bd, bcbd);
	add(acad, bcbd, result);
	if (DEBUG) {
		cout << "s1:" << s1 << ", s2:" << s2 << ", result:" << result << endl;
	}

}

int main(int argc, char * argv[]) {
	string line1, line2, str1, str2, result;
	//bool firstLine = true;
	while (getline(cin, line1)) {
		str1.clear();
		str2.clear();
		getline(cin, line2);
		bool begin0 = true;
		for (int i = 0; i < line1.length(); i++) {
			if (begin0 && line1.substr(i, 1).compare("0") == 0) {
				continue;
			}
			begin0 = false;
			str1.append(line1.substr(i, 1));
		}
		begin0 = true;
		for (int i = 0; i < line2.length(); i++) {
			if (begin0 && line2.substr(i, 1).compare("0") == 0) {
				continue;
			}
			begin0 = false;
			str2.append(line2.substr(i, 1));
		}
		stringstream ss;
		ss << str1;
		str1.clear();
		ss >> str1;
		ss.clear();
		ss << str2;
		str2.clear();
		ss >> str2;
		multiply(str1, str2, result);

		cout << result << endl;
	}
	return 0;
}

//
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//
//void mult(char a[],char b[],char c[])
//{
//    int len_a = strlen(a),len_b = strlen(b);
//    int i,j;
//    memset(c,'0',len_a+len_b+1);
//    for ( i = 0; i < len_a; ++i)
//    {
//        int carry = 0;
//        for (j = 0; j < len_b;++j)
//        {
//            int iTemp = (a[i]-'0') * (b[j]-'0');
//            int icTemp = c[i+j];
//            icTemp  += iTemp + carry; //防止溢出
//            carry = (icTemp-'0') /10;
//            c[i+j]  = (icTemp-'0') % 10 + '0';
//        }
//        if (carry)
//            c[i+j]  += carry;
//    }
//    for (i = len_a + len_b; i >= 0 && c[i] == '0';--i);
//
//    c[i+1] = 0;
//
//}
//
//int main()
//{
//    char a[255],b[255];
//    while (scanf("%s %s",a,b) == 2)
//    {
//        if (!strcmp(a,"0") || !strcmp(b,"0"))
//        {
//            printf("0/n");
//            continue;
//        }
//        char sum[510] = {0};
//        reverse(a,a+strlen(a));
//        reverse(b,b+strlen(b));
//        mult(a,b,sum);
//        reverse(sum,sum+strlen(sum));
//        printf("%s/n",sum);
//    }
//}
