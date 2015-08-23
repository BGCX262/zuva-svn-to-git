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

public class Solution_UniquePathsWithObstacles {

	public int uniquePathsWithObstacles(int[][] obstacleGrid) {
		int m = obstacleGrid.length;
		int n = obstacleGrid[0].length;
		int[][] board = new int[m][n];

		for (int j = 0; j < n; j++) {
			if (obstacleGrid[0][j] == 0) {
				board[0][j] = 1;
			} else {
				for (int j2 = j; j2 < n; j2++) {
					board[0][j2] = 0;
				}
				break;
			}
		}
		for (int i = 0; i < m; i++) {
			if (obstacleGrid[i][0] == 0) {
				board[i][0] = 1;
			} else {
				for (int i2 = i; i2 < m; i2++) {
					board[i2][0] = 0;
				}
				break;
			}
		}

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (obstacleGrid[i][j] == 0) {
					board[i][j] = board[i - 1][j] + board[i][j - 1];
				} else {
					board[i][j] = 0;
				}
			}
		}

		return board[m - 1][n - 1];
	}

	public static void main(String[] args) {
		Solution_UniquePathsWithObstacles solution_UniquePathsWithObstacles = new Solution_UniquePathsWithObstacles();
		// System.out.println(solution.uniquePathsWithObstacles(3, 7));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
