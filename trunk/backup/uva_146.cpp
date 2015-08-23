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

static int DAY_START = 480;
static int DAY_END = 1080;
static int EVE_START = 1080;
static int EVE_END = 1320;
static int NIG_START1 = 1320;
static int NIG_END1 = 1440;
static int NIG_START2 = 0;
static int NIG_END2 = 480;

static float Charg[5][3] = { { 0.10, 0.06, 0.02 }, { 0.25, 0.15, 0.05 }, { 0.53, 0.33, 0.13 }, { 0.87, 0.47, 0.17 }, { 1.44, 0.80, 0.30 } };

int calMinutes(int & start, int & end, int & rangeStart, int & rangeEnd) {
	int re = 0;
	if (start < end) {
		if (start >= rangeStart && start <= rangeEnd && end >= rangeStart && end <= rangeEnd) {
			re = end - start;
		} else if (start >= rangeStart && start <= rangeEnd && end > rangeEnd) {
			re = rangeEnd - start;
		} else if (start < rangeStart && end >= rangeStart && end <= rangeEnd) {
			re = end - rangeStart;
		} else if (start < rangeStart && end > rangeEnd) {
			re = rangeEnd - rangeStart;
		}
	} else {
		// end less than start
		if (start < rangeStart || end > rangeEnd) {
			re = (rangeEnd - rangeStart);
		} else {
			if (start >= rangeStart && start <= rangeEnd) {
				re = rangeEnd - start;
			}
			if (end >= rangeStart && end <= rangeEnd) {
				re += (end - rangeStart);
			}
		}
	}
	return re;
}

int calDayMinutes(int & start, int & end) {
	return calMinutes(start, end, DAY_START, DAY_END);
}

int calEveMinutes(int & start, int & end) {
	return calMinutes(start, end, EVE_START, EVE_END);
}

int calNightMinutes(int & start, int & end) {
	int re = calMinutes(start, end, NIG_START1, NIG_END1);
	re += calMinutes(start, end, NIG_START2, NIG_END2);
	return re;
}

int main(int argc, char * argv[]) {

	while (true) {
		string dist;
		string call;
		int startH;
		int startM;
		int endH;
		int endM;
		cin >> dist;
		if (dist == "#")
			break;
		cin >> call;
		cin >> startH;
		cin >> startM;
		cin >> endH;
		cin >> endM;
		int start = startH * 60 + startM;
		int end = endH * 60 + endM;
		int dayMins = calDayMinutes(start, end);
		int eveMins = calEveMinutes(start, end);
		int nightMins = calNightMinutes(start, end);
		float cost = dayMins * Charg[dist[0] - 'A'][0] + eveMins * Charg[dist[0] - 'A'][1] + nightMins * Charg[dist[0] - 'A'][2];

		if (DEBUG) {
			cout << call << " dist:" << dist << " " << startH << ":" << startM << " " << endH << ":" << endM << endl;
			cout << " day:" << dayMins << " eve:" << eveMins << " night:" << nightMins << " cost:" << cost << endl;
		} else {

			printf("%10s%6d%6d%6d%3c%8.2lf\n", call.c_str(), dayMins, eveMins, nightMins, dist[0], cost);
			//			cout << setw(10) << call;
			//			cout << setw(6) << dayMins;
			//			cout << setw(6) << eveMins;
			//			cout << setw(6) << nightMins;
			//			cout << setw(3) << dist;
			//			cout << setw(8) << cost << endl;
		}
	}

	return 0;
}
