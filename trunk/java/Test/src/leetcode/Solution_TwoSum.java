package leetcode;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Solution_TwoSum {
	public int[] twoSum(int[] numbers, int target) {
		Map<Integer, Integer> map = new HashMap<Integer, Integer>();
		for (int i = 0; i < numbers.length; i++) {
			map.put(numbers[i], i);
		}
		for (int i = 0; i < numbers.length; i++) {
			Integer j = map.get(target - numbers[i]);
			if (j != null && i != j) {
				return new int[] { i + 1, j + 1 };
			}
		}
		return null;
	}
}