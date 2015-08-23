package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Solution_3SumCloset {

	private int distance(int a, int b) {
		if (a > 0 && b > 0) {
			return Math.abs(a - b);
		} else if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
			return Math.abs(a) + Math.abs(b);
		} else {
			return Math.abs(Math.abs(a) - Math.abs(b));
		}
	}

	public int threeSumClosest(int[] num, int target) {
		Arrays.sort(num);

		if (num.length <= 3) {
			int t = 0;
			for (int n : num) {
				t += n;
			}
			return t;
		}
		int minDiff = distance(target, num[0] + num[1] + num[2]);
		int min = num[0] + num[1] + num[2];
		for (int i = 0; i < num.length; i++) {
			int j = i + 1, k = num.length - 1;
			while (k > j) {
				int sum = num[i] + num[j] + num[k];
				int diff = distance(target, sum);
				if (sum > target) {
					k--;
				} else {
					j++;
				}

				if (diff < minDiff) {
					minDiff = diff;
					min = sum;
				}
			}
		}
		return min;
	}

	public static void main(String[] args) {
		Solution_3SumCloset solution_3SumCloset = new Solution_3SumCloset();
		System.out.println(solution_3SumCloset.threeSumClosest(new int[] { 0, 2, 1, -3 }, 1));
		System.out.println(solution_3SumCloset.threeSumClosest(new int[] { -1, 2, 1, -4 }, 1));

	}
}
