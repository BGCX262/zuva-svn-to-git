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

public class Solution_SpiralOrderMatrix {

	private int generateOne(int[][] matrix, int x, int y, int n, int start) {
		int num = 0;
		for (int j = 0; j < n; j++) {
			matrix[x][y + j] = start + num++;
		}
		for (int i = 1; i < n; i++) {
			matrix[x + i][y + n - 1] = start + num++;
		}
		for (int j = n - 2; j >= 0; j--) {
			matrix[x + n - 1][y + j] = start + num++;
		}
		for (int i = n - 2; i > 0; i--) {
			matrix[x + i][y] = start + num++;
		}
		return num;
	}

	public int[][] generateMatrix(int n) {
		int[][] matrix = new int[n][n];
		int start = 1;
		for (int i = 0; i < n; i++) {
			int num = generateOne(matrix, i, i, n - i * 2, start);
			start += num;
		}

		return matrix;
	}

	public static void main(String[] args) {
		Solution_SpiralOrderMatrix solution_SpiralOrderMatrix = new Solution_SpiralOrderMatrix();
		System.out.println(solution_SpiralOrderMatrix.generateMatrix(3));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
