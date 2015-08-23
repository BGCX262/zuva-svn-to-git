package backup;

import java.util.Arrays;
import java.util.Collections;

public class Solution3_BinarySearchError {
	int solution(int[] A, int X) {
		int N = A.length;
		if (N == 0) {
			return -1;
		}

		int l = 0;
		int r = N - 1;
		while (l < r - 1) {
			int m = (l + r) / 2;
			if (A[m] > X) {
				r = m - 1;
			} else {
				l = m;
			}
		}
		if (A[l] == X || A[r] == X) {
			return l;
		}
		return -1;
	}

	public static void main(String[] args) {
		Solution3_BinarySearchError solution3_BinarySearchError = new Solution3_BinarySearchError();
		int[] a1 = { 2000000000, 1, 2, 5, 9, 9 };
		int[] a = { 1, 2000000000 };
		int[] a2 = { 1 };
		System.out.println(solution3_BinarySearchError.solution(a, 2000000000));
	}
}
