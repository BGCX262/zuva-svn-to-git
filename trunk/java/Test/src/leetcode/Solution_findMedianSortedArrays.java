package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Solution_findMedianSortedArrays {
	public double findMedianSortedArrays(int A[], int B[]) {
		List<Integer> list = new ArrayList<Integer>();
		for (int a : A) {
			list.add(a);
		}
		for (int b : B) {
			list.add(b);
		}
		Collections.sort(list);
		if (list.size() % 2 == 0) {
			return (new Double(list.get(list.size() / 2 - 1)) + (new Double(list.get(list.size() / 2)))) / 2.0;
		} else {
			return list.get(list.size() / 2);
		}
	}
}