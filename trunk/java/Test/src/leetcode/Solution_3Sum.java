package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

interface inter {
	void a();
}

class ThreeNum implements Comparable<ThreeNum> {
	Integer one;
	Integer two;
	Integer three;

	public ThreeNum(Integer a, Integer b, Integer c) {
		this.one = a;
		this.two = b;
		this.three = c;
	}

	public boolean equals(Object o) {
		return (o instanceof ThreeNum) && (((ThreeNum) o).one).equals(this.one) && (((ThreeNum) o).two).equals(this.two)
				&& (((ThreeNum) o).three).equals(this.three);
	}

	public int hashCode() {
		return one.hashCode() + two.hashCode() + three.hashCode();
	}

	@Override
	public int compareTo(ThreeNum o) {
		return 0;
	}
}

public class Solution_3Sum {
	public List<List<Integer>> threeSum(int[] num) {
		Arrays.sort(num);
		List<List<Integer>> result = new ArrayList<List<Integer>>();
		Set<ThreeNum> set = new HashSet<ThreeNum>();

		for (int i = 0; i < num.length - 2; i++) {
			if (num[i] > 0)
				break;
			for (int j = i + 1; j < num.length - 1; j++) {
				int thisTwo = num[i] + num[j];
				if (thisTwo > 0)
					break;
				for (int k = j + 1; k < num.length; k++) {
					if (num[k] + thisTwo == 0) {
						set.add(new ThreeNum(num[i], num[j], num[k]));
						break;
					}
				}
			}
		}
		for (ThreeNum t : set) {
			List<Integer> list = new ArrayList<Integer>();
			list.add(t.one);
			list.add(t.two);
			list.add(t.three);
			result.add(list);
		}

		return result;
	}

	public static void main(String[] args) {
		Solution_3Sum solution_3Sum = new Solution_3Sum();
		System.out.println(solution_3Sum.threeSum(new int[] { -1, 0, 1, 2, -1, -4 }));
		System.out.println(solution_3Sum.threeSum(new int[] { 7, -1, 14, -12, -8, 7, 2, -15, 8, 8, -8, -14, -4, -5, 7, 9, 11, -4, -15, -6, 1, -14, 4, 3, 10, -5, 2,
				1, 6, 11, 2, -2, -5, -7, -6, 2, -15, 11, -6, 8, -4, 2, 1, -1, 4, -6, -15, 1, 5, -15, 10, 14, 9, -8, -6, 4, -6, 11, 12, -15, 7, -1, -9, 9, -1,
				0, -4, -1, -12, -2, 14, -9, 7, 0, -3, -4, 1, -2, 12, 14, -10, 0, 5, 14, -1, 14, 3, 8, 10, -8, 8, -5, -2, 6, -11, 12, 13, -7, -12, 8, 6, -13,
				14, -2, -5, -11, 1, 3, -6 }));
	}
}
