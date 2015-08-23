#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001
#define PI 3.141592653589793
#define EARTH_RAD 6378

struct City {
	char name[36];
	double latitude;
	double longitude;
};

struct City cities[101];
int polSize;

void printAllCity() {
	int i;
	for (i = 0; i < polSize; i++) {
		printf("%s, latitude:%f, longitude:%f\n", cities[i].name, cities[i].latitude, cities[i].longitude);
	}
}
/**
 * great circle distance
 */
double gcDistance(double pLat, double pLong, double qLat, double qLong, double radius) {
	pLat *= PI / 180;
	pLong *= PI / 180;
	qLat *= PI / 180;
	qLong *= PI / 180;
	double dlon = qLong - pLong;
	double dlat = qLat - pLat;
	double a = (sin(dlat / 2)) * (sin(dlat / 2)) + cos(pLat) * cos(qLat) * (sin(dlon / 2)) * (sin(dlon / 2));
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return radius * c;
}

int roundInteger(double d) {
	return (int) (d + 0.5f);
}

/**
 * 535
 */
int main(int argc, char * argv[]) {
	int i, j, len;
	char s[36], s2[36];
	polSize = 0;
	while (scanf("%s", s) && s[0] != '#') {
		double a, b;
		scanf("%lf %lf", &a, &b);
		strcpy(cities[polSize].name, s);
		cities[polSize].latitude = a;
		cities[polSize].longitude = b;
		polSize++;
	}
	if (DEBUG) {
		printAllCity();
	}

	while (scanf("%s %s", s, s2) && s[0] != '#') {
		printf("%s - %s\n", s, s2);
		for (i = 0; i < polSize && strcmp(cities[i].name, s) != 0; i++)
			;

		for (j = 0; j < polSize && strcmp(cities[j].name, s2) != 0; j++)
			;

		if (i == polSize || j == polSize) {
			printf("Unknown\n");
			continue;
		}

		printf("%d km\n", roundInteger(gcDistance(cities[i].latitude, cities[i].longitude, cities[j].latitude, cities[j].longitude,
		EARTH_RAD)));
	}
	return 0;
}
