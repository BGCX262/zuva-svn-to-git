package backup;
import java.util.HashSet;
import java.util.Set;

/*
 http://stackoverflow.com/questions/5730330/codility-question-absolute-distinct-count

 count the number of elements in an array a which are absolute distinct, what it means is if an array had -3 and 3 in it these numbers are not distinct because|-3|=|3|.
 i think an example would clear it up better
 a={-5,-3,0,1,-3} the result would be 4 because there are 4 absolute distinct elements in this array.

 length would be <=10000, and most importantly it stated that assume that the array is sorted in ascending order
 */

public class AbsDistinct {
	private static int countDistinct(int[] nums) {

		Set<Integer> s = new HashSet<Integer>();
		int len = nums.length;
		for (int i = 0; i < len; i++) {
			s.add(Math.abs(nums[i]));
		}
		return s.size();
	}

	public static void tests() {
		int[] A = {};
		Assert.assertEquals(countDistinct(A), 0, "Pusta");
		int[] B = { 0 };
		Assert.assertEquals(countDistinct(B), 1, "Jeden element");
		int[] C = { 1, 1, 1, 1 };
		Assert.assertEquals(countDistinct(C), 1, "Ten sam element");
		int[] D = { -5, -3, 0, 1, -3 };
		Assert.assertEquals(countDistinct(D), 4, "Przyklad 1");
		int[] E = { -9, -6, -5, -5, -5, -5, -3, -3, 0, 0, 1, 5, 6, 7, 7, 8 };
		Assert.assertEquals(countDistinct(E), 8, "Przyklad 2");
	}
}