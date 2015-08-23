package leetcode;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

// class Interval {
// int start;
// int end;
//
// Interval() {
// start = 0;
// end = 0;
// }
//
// Interval(int s, int e) {
// start = s;
// end = e;
// }
// }

public class Solution_UniquePaths {

	public int uniquePaths(int m, int n) {
		int[][] board = new int[m][n];

		for (int j = 0; j < n; j++) {
			board[0][j] = 1;
		}
		for (int i = 0; i < m; i++) {
			board[i][0] = 1;
		}

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				board[i][j] = board[i - 1][j] + board[i][j - 1];
			}
		}

		return board[m - 1][n - 1];
	}

	public static void main(String[] args) {
		Solution_UniquePaths solution_UniquePaths = new Solution_UniquePaths();
		System.out.println(solution_UniquePaths.uniquePaths(3, 7));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
