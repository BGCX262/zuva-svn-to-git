package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_NQueensII {

	private int num;

	private boolean valid(char[][] board, int x, int y, int n) {
		// System.out.println("fill x "+x+" y "+y +" c " + c);
		// for (int i = 0; i < n; i++) {
		// for (int j = 0; j < n; j++) {
		// System.out.print(board[i][j] + " ");
		// }
		// System.out.println("");
		// }
		// System.out.println("");

		for (int i = 0; i < n; i++) {
			if (i != x) {
				if (board[i][y] == 'Q')
					return false;
			}
		}

		int row = x - 1, col = y + 1;
		while (row >= 0 && col < n) {
			if (board[row--][col++] == 'Q')
				return false;
		}
		row = x + 1;
		col = y + 1;
		while (row < n && col < n) {
			if (board[row++][col++] == 'Q')
				return false;
		}

		row = x - 1;
		col = y - 1;
		while (row >= 0 && col >= 0) {
			if (board[row--][col--] == 'Q')
				return false;
		}

		row = x + 1;
		col = y - 1;
		while (row < n && col >= 0) {
			if (board[row++][col--] == 'Q')
				return false;
		}
		return true;
	}

	private void dfs(char[][] board, int curr, int n) {
		// System.out.println("dfs " + curr);
		// for (int i = 0; i < n; i++) {
		// for (int j = 0; j < n; j++) {
		// System.out.print(board[i][j] + " ");
		// }
		// System.out.println("");
		// }
		// System.out.println("");

		if (curr >= n) {
			num++;
			return;
		}
		for (int j = 0; j < n; j++) {
			if (board[curr][j] == '.' && valid(board, curr, j, n)) {
				board[curr][j] = 'Q';
				dfs(board, curr + 1, n);
				board[curr][j] = '.';
			}
		}
	}

	public int totalNQueens(int n) {
		char[][] board = new char[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = '.';
			}
		}
		dfs(board, 0, n);
		return num;
	}

	public static void main(String[] args) {
		Solution_NQueensII solution_NQueensII = new Solution_NQueensII();
		System.out.println(solution_NQueensII.totalNQueens(4));
	}
}
