package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

class FourNum {
	Integer one;
	Integer two;
	Integer three;
	Integer four;

	public FourNum(Integer a, Integer b, Integer c, Integer d) {
		this.one = a;
		this.two = b;
		this.three = c;
		this.four = d;
	}

	public boolean equals(Object o) {
		return (o instanceof FourNum) && (((FourNum) o).one).equals(this.one) && (((FourNum) o).two).equals(this.two)
				&& (((FourNum) o).three).equals(this.three) && (((FourNum) o).four).equals(this.four);
	}

	public int hashCode() {
		return one.hashCode() + two.hashCode() + three.hashCode() + four.hashCode();
	}
}

public class Solution_4Sum {

	public List<List<Integer>> fourSum(int[] num, int target) {
		Set<Integer> twoSet = new HashSet<Integer>();
		for (int i = 0; i < num.length - 1; i++) {
			for (int j = i + 1; j < num.length; j++) {
				twoSet.add(num[i] + num[j]);
			}
		}

		Arrays.sort(num);
		List<List<Integer>> result = new ArrayList<List<Integer>>();
		Set<FourNum> set = new HashSet<FourNum>();

		for (int i = 0; i < num.length - 3; i++) {
			if (num[i] >= 0 && num[i] > target) {
				break;
			}
			for (int j = i + 1; j < num.length - 2; j++) {
				int thisTwo = num[i] + num[j];
				if (thisTwo >= 0 && thisTwo > target) {
					break;
				}

				if (!twoSet.contains(target - thisTwo)) {
					continue;
				}

				for (int k = j + 1; k < num.length - 1; k++) {
					int thisThree = thisTwo + num[k];
					if (thisThree >= 0 && thisThree > target) {
						break;
					}
					for (int m = k + 1; m < num.length; m++) {
						int thisFour = thisThree + num[m];
						if (thisFour >= 0 && thisFour > target) {
							break;
						} else if (thisFour == target) {
							set.add(new FourNum(num[i], num[j], num[k], num[m]));
						}
					}
				}
			}
		}
		for (FourNum t : set) {
			List<Integer> list = new ArrayList<Integer>();
			list.add(t.one);
			list.add(t.two);
			list.add(t.three);
			list.add(t.four);
			result.add(list);
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_4Sum solution_4Sum = new Solution_4Sum();
		System.out.println(solution_4Sum.fourSum(new int[] { 1, -2, -5, -4, -3, 3, 3, 5 }, -11));
		// System.out.println(solution.fourSum(new int[] { 1, 0, -1, 0, -2, 2 },
		// 0));

	}
}
