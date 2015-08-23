#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

void swapChar(char * str1, char * str2) {
	char t = *str1;
	*str1 = *str2;
	*str2 = t;
}

/*
 * bin[0][0]=bin1's Brown bottle number
 * bin[0][1]=bin1's Green bottle number
 * bin[0][2]=bin1's Clear bottle number
 */
static int bin[3][3];
static unsigned int min;
static char minStr[4];
static char color[3] = { 'B', 'G', 'C' };
int calculate_move(char str[]) {
	int i, result = 0;
	for (i = 0; i < 3; i++) {
		if (str[0] == color[i]) {
			result += bin[1][i] + bin[2][i];
			break;
		}
	}
	for (i = 0; i < 3; i++) {
		if (str[1] == color[i]) {
			result += bin[0][i] + bin[2][i];
			break;
		}
	}
	for (i = 0; i < 3; i++) {
		if (str[2] == color[i]) {
			result += bin[0][i] + bin[1][i];
			break;
		}
	}
	return result;
}

void permuteStr(char * str, int i) {
	if (i == strlen(str) - 1) {
		int move = calculate_move(str);
		if (DEBUG) {
			printf("%s with %d move\n", str, move);
		}
		if (move < min) {
			min = move;
			minStr[0] = str[0];
			minStr[1] = str[1];
			minStr[2] = str[2];
			minStr[3] = '\0';
		} else if (move == min) {
			if (strcmp(minStr, str) > 0) {
				minStr[0] = str[0];
				minStr[1] = str[1];
				minStr[2] = str[2];
				minStr[3] = '\0';
			}
		}
	} else {
		int j;
		for (j = i; j < strlen(str); j++) {
			swapChar(&str[i], &str[j]);
			permuteStr(str, i + 1);
			swapChar(&str[i], &str[j]);
		}
	}
}

int main(int argc, char * argv[]) {
	char bins[] = "BCG";
	while (scanf("%d %d %d %d %d %d %d %d %d\n", &bin[0][0], &bin[0][1], &bin[0][2], &bin[1][0], &bin[1][1], &bin[1][2], &bin[2][0], &bin[2][1], &bin[2][2])
			== 9) {
		min = 01 << 31;
		permuteStr(bins, 0);
		printf("%c%c%c %d\n", minStr[0], minStr[1], minStr[2], min);
	}
	return 0;
}

