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

public class Solution_RotateImage {

	private void copy(int[][] matrix, int x, int y) {
		int temp = matrix[x][y];
		int n = matrix.length;
		matrix[x][y] = matrix[n - 1 - y][x];
		matrix[n - 1 - y][x] = matrix[n - 1 - x][n - 1 - y];
		matrix[n - 1 - x][n - 1 - y] = matrix[y][n - 1 - x];
		matrix[y][n - 1 - x] = temp;
	}

	private void rotate(int[][] matrix, int offset, int len) {
		for (int i = 0; i < len - 1; i++) {
			copy(matrix, offset, offset + i);
		}
	}

	public void rotate(int[][] matrix) {
		int n = matrix.length;
		for (int i = 0; i < n / 2; i++) {
			rotate(matrix, i, n - 2 * i);
		}
	}

	public static void main(String[] args) {
		Solution_RotateImage solution_RotateImage = new Solution_RotateImage();
		int[][] arr = new int[][] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
		solution_RotateImage.rotate(arr);
		for (int i = 0; i < arr.length; i++) {
			for (int j = 0; j < arr[i].length; j++) {
				System.out.print(arr[i][j] + ", ");
			}
			System.out.println("\n");
		}

	}
}
