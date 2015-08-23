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

import javax.swing.border.Border;
import javax.swing.text.ChangedCharSetException;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_Sudoku {

	public boolean isValidSudoku(char[][] board) {
		if (board == null || board.length != 9) {
			return false;
		}

		Set<Integer> set = new HashSet<Integer>();
		for (int i = 0; i < board.length; i++) {
			set.clear();
			for (int j = 0; j < board[i].length; j++) {
				if (board[i][j] == '.') {
					continue;
				}
				Integer n = board[i][j] - '0';
				if (n < 0 || n > 9) {
					return false;
				}
				if (set.contains(n)) {
					return false;
				}
				set.add(n);
			}
		}
		for (int j = 0; j < board.length; j++) {
			set.clear();
			for (int i = 0; i < board[j].length; i++) {
				if (board[i][j] == '.') {
					continue;
				}
				Integer n = board[i][j] - '0';
				if (n < 0 || n > 9) {
					return false;
				}
				if (set.contains(n)) {
					return false;
				}
				set.add(n);
			}
		}

		for (int i = 0; i < board.length - 2; i += 3) {
			for (int j = 0; j < board[i].length - 2; j += 3) {
				set.clear();
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						if (board[i + x][j + y] == '.') {
							continue;
						}
						Integer n = board[i + x][j + y] - '0';
						if (n < 0 || n > 9) {
							return false;
						}
						if (set.contains(n)) {
							return false;
						}
						set.add(n);
					}
				}
			}
		}

		return true;
	}

	public boolean isValidSudoku(char[][] board, int x, int y) {
		Set<Integer> set = new HashSet<Integer>();
		for (int j = 0; j < 9; j++) {
			if (board[x][j] == '.') {
				continue;
			}
			Integer n = board[x][j] - '0';
			if (set.contains(n)) {
				return false;
			}
			set.add(n);
		}
		set.clear();
		for (int i = 0; i < 9; i++) {
			if (board[i][y] == '.') {
				continue;
			}
			Integer n = board[i][y] - '0';
			if (set.contains(n)) {
				return false;
			}
			set.add(n);
		}
		set.clear();

		int startX, startY;
		if (x < 3) {
			startX = 0;
		} else if (x < 6) {
			startX = 3;
		} else {
			startX = 6;
		}
		if (y < 3) {
			startY = 0;
		} else if (y < 6) {
			startY = 3;
		} else {
			startY = 6;
		}

		set.clear();
		for (int i = startX; i < startX + 3; i++) {
			for (int j = startY; j < startY + 3; j++) {
				if (board[i][j] == '.') {
					continue;
				}
				Integer n = board[i][j] - '0';
				if (set.contains(n)) {
					return false;
				}
				set.add(n);
			}
		}
		return true;
	}

	private void printInfo(List<List<Set<Integer>>> av) {
		System.out.println("=====================================================");
		for (int i = 0; i < av.size(); i++) {
			for (int j = 0; j < av.get(i).size(); j++) {
				System.out.print(av.get(i).get(j));
				System.out.print(", ");
			}
			System.out.println("");
		}
	}

	public void solveSudoku(char[][] board) {
		List<List<Set<Integer>>> av = new ArrayList<List<Set<Integer>>>();
		for (int i = 0; i < 9; i++) {
			av.add(new ArrayList<Set<Integer>>());
			for (int j = 0; j < 9; j++) {
				av.get(i).add(new HashSet<Integer>());
				for (int k = 1; k <= 9; k++) {
					av.get(i).get(j).add(k);
				}
			}
		}
		//printInfo(av);

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.') {
					continue;
				}
				av.get(i).get(j).clear();
				int n = board[i][j] - '0';
				int row, col;
				for (col = 0; col < 9; col++) {
					av.get(i).get(col).remove(n);
				}
				for (row = 0; row < 9; row++) {
					av.get(row).get(j).remove(n);
				}
			}
		}

		for (int i = 0; i < board.length - 2; i += 3) {
			for (int j = 0; j < board[i].length - 2; j += 3) {
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						int i2 = i + x;
						int j2 = j + y;
						if (board[i2][j2] == '.') {
							continue;
						}
						Integer n = board[i2][j2] - '0';
						for (int row = 0; row < 3; row++) {
							for (int col = 0; col < 3; col++) {
								int i3 = i + row;
								int j3 = j + col;
								av.get(i3).get(j3).remove(n);
							}
						}
					}
				}
			}
		}

		//printInfo(av);

		dfs(board, 0, 0, av);
	}

	private boolean dfs(char[][] board, int x, int y, List<List<Set<Integer>>> av) {
		if (x > 8) {
			return true;
		}
		int nextY, nextX;
		if (y == 8) {
			nextX = x + 1;
			nextY = 0;
		} else {
			nextX = x;
			nextY = y + 1;
		}
		if (board[x][y] == '.') {
			Iterator<Integer> it = av.get(x).get(y).iterator();
			while (it.hasNext()) {
				Integer n = it.next();
				board[x][y] = n.toString().charAt(0);
				if (isValidSudoku(board, x, y)) {
					if (dfs(board, nextX, nextY, av)) {
						return true;
					}
				}
			}
			board[x][y] = '.';
			return false;
		} else {
			return dfs(board, nextX, nextY, av);
		}
	}

	public static void main(String[] args) {
		Solution_Sudoku solution_Sudoku = new Solution_Sudoku();
		String[] in = { "..9748...", "7........", ".2.1.9...", "..7...24.", ".64.1.59.", ".98...3..", "...8.3.2.", "........6", "...2759.." };
		char[][] inChar = new char[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				inChar[i][j] = in[i].charAt(j);
			}
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				System.out.print(inChar[i][j]);
			}
			System.out.print("\n");
		}
		solution_Sudoku.solveSudoku(inChar);
		System.out.println("solved\n");

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				System.out.print(inChar[i][j]);
			}
			System.out.print("\n");
		}
	}
}
