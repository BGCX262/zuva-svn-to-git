package backup;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * find the biggest circle
 */
public class Solution2_FindBiggestCircle2 {

	public int solution(int[] A) {
		int max = 0, curr, counter;
		Set<Integer> globalVisitedSet = new HashSet<Integer>();
		Set<Integer> visitedSet = new HashSet<Integer>();
		for (int i = 0; i < A.length; i++) {
			curr = A[i];
			if (globalVisitedSet.contains(curr)) {
				continue;
			}
			globalVisitedSet.add(curr);
			visitedSet.clear();
			counter = 1;
			visitedSet.add(0);
			while (!visitedSet.contains(A[curr])) {
				visitedSet.add(curr);
				globalVisitedSet.add(curr);
				curr = A[curr];
				counter++;
			}
			if (counter > max) {
				max = counter;
			}
		}
		return max;
	}

	public static void main(String[] args) {
		Solution2_FindBiggestCircle2 solution = new Solution2_FindBiggestCircle2();
		int[] a = { 5, 4, 0, 3, 1, 6, 2 };
		System.out.println(solution.solution(a));
	}
}
