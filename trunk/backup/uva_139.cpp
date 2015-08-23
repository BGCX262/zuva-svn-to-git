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
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG 1

struct Code {
	string num;
	string name;
	float price;
};

struct Log {
	string num;
	string lnum;
	int duration;
	struct Code code;
};

struct Code getCode(string & num, map<string, struct Code> & codes) {
	struct Code c;
	c.num = "";
	c.name = "Unknown";

	if (num[0] != '0') {
		//local
		c.num = "";
		c.name = "Local";
		c.price = 0.00;
		return c;
	}

	map<string, struct Code>::iterator it;
	for (it = codes.begin(); it != codes.end(); it++) {
		if (num.find((*it).first) == 0) {
			if ((*it).first.substr(0, 2) == "00" && (num.size() - (*it).first.size() >= 4) && (num.size() - (*it).first.size() <= 10)) {
				if (c.num.size() < (*it).first.size())
					c = (*it).second;
			} else if ((*it).first.substr(0, 1) == "0" && (num.size() - (*it).first.size() >= 4) && (num.size() - (*it).first.size() <= 7)) {
				if (c.num.size() < (*it).first.size())
					c = (*it).second;
			}
		}
	}
	return c;
}

int main(int argc, char * argv[]) {
	string str, str1, str2;
	bool firstPart = true;
	map<string, struct Code> codes;
	vector<struct Log> logs;
	while (getline(cin, str)) {
		if (str == "000000") {
			firstPart = false;
			continue;
		}
		if (str == "#")
			break;
		stringstream ss(str);
		ss >> str1;
		str2 = str.substr(str.find(str1) + str1.size(), str.size() - str1.size());
		if (firstPart) {
			struct Code c;
			c.num = str1;
			stringstream ss2(str2);
			string name;
			getline(ss2, name, '$');
			c.name = name;
			string price;
			getline(ss2, price, '$');
			stringstream ss3(price);
			ss3 >> c.price;
			c.price *= 0.01;
			codes[c.num] = c;
		} else {
			struct Log log;
			log.num = str1;
			stringstream ss2(str2);
			ss2 >> log.duration;
			log.code = getCode(log.num, codes);
			log.lnum = log.num.substr(log.code.num.size(), log.num.size() - log.code.num.size());
			logs.push_back(log);
		}
	}
	int size = logs.size();
	for (int i = 0; i < size; i++) {
		if (logs[i].code.name != "Unknown") {
			printf("%-16s%-26s%9s%5d%6.2lf%7.2lf\n", logs[i].num.c_str(), logs[i].code.name.c_str(), logs[i].lnum.c_str(), logs[i].duration,
					logs[i].code.price, logs[i].code.price * logs[i].duration);
		} else {
			printf("%-16s%-26s%14d%13s\n", logs[i].num.c_str(), logs[i].code.name.c_str(), logs[i].duration, "-1.00");
		}
	}
	return 0;
}
