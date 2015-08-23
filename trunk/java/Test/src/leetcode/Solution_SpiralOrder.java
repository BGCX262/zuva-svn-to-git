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

public class Solution_SpiralOrder {

	private List<Integer> spiralOne(int[][] matrix, int x, int y, int m, int n) {
		List<Integer> result = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			result.add(matrix[x][y + i]);
		}
		for (int i = 1; i < m; i++) {
			result.add(matrix[x + i][y + n - 1]);
		}
		if (m > 1) {
			for (int i = 1; i < n; i++) {
				result.add(matrix[x + m - 1][y + n - 1 - i]);
			}
		}
		if (n > 1) {
			for (int i = 1; i < m - 1; i++) {
				result.add(matrix[x + m - 1 - i][y]);
			}
		}
		return result;
	}

	public List<Integer> spiralOrder(int[][] matrix) {
		List<Integer> result = new ArrayList<Integer>();
		int m = matrix.length;
		if (m == 0) {
			return result;
		}
		int n = matrix[0].length;
		for (int i = 0; m > 0 && n > 0; i++, m -= 2, n -= 2) {
			List<Integer> oneRound = spiralOne(matrix, i, i, m, n);
			result.addAll(oneRound);
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_SpiralOrder solution_SpiralOrder = new Solution_SpiralOrder();
		System.out.println(solution_SpiralOrder.spiralOrder(new int[][] { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }));
		// System.out.println(solution.spiralOrder(new int[][] { { 1, 2, 3 }, {
		// 4, 5, 6 } }));
		System.out.println(solution_SpiralOrder.spiralOrder(new int[][] { { 1 }, { 2 }, { 3 } }));
		System.out.println(solution_SpiralOrder.spiralOrder(new int[][] { { 1, 2 } }));
	}
}
