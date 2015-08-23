#include<stdio.h>
#include<string.h>
#define DEBUG 0
int H, K, maxValueStamps[15], maxValue;

int judge(int target, int curPosition, int num, int total, int *stamps, int end) {
	int i, j;
	if (DEBUG) {
		/*printf("judge:%d cur:%d num:%d tot:%d end:%d\n", target, curPosition, num, total, end);*/
	}

	if (total == target)
		return 1;
	else if (curPosition == end || num == H)
		return 0;
	if (judge(target, curPosition + 1, num, total, stamps, end))
		return 1;
	if (judge(target, curPosition, num + 1, total + stamps[curPosition], stamps, end))
		return 1;
	return 0;
}
void dfs(int curValue, int *stamps, int end) {
	int i, j;
	if (DEBUG) {
		printf("%d [", curValue);
		for (i = 0; i < end; i++) {
			printf("%d ", stamps[i]);
		}
		printf("] %d\n", end);
	}

	if (judge(curValue, 0, 0, 0, stamps, end)){
		if(DEBUG){
			/*printf("judge return 1\n");*/
		}
		dfs(curValue + 1, stamps, end);
	}

	if (end < K) {
		stamps[end] = curValue;
		end++;
		dfs(curValue + 1, stamps, end);
		end--;
		stamps[end] = -1;
	}
	if (curValue - 1 > maxValue) {
		maxValue = curValue - 1;
		memcpy(maxValueStamps, stamps, sizeof(maxValueStamps));
	}
}

int main() {
	int i, j, k, stamps[15];
	while (1) {
		scanf("%d%d", &H, &K);
		if (H == 0)
			break;
		memset(stamps, -1, sizeof(stamps));
		maxValue = 0;
		dfs(1, stamps, 0);
		for (i = 0; i < K; i++)
			printf("%3d", maxValueStamps[i]);
		printf(" ->");
		printf("%3d\n", maxValue);
	}
	return 0;
}

