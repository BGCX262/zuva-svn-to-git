package backup;
/*
http://stackoverflow.com/questions/5730330/codility-question-absolute-distinct-count

count the number of elements in an array a which are absolute distinct, what it means is if an array had -3 and 3 in it these numbers are not distinct because|-3|=|3|.
i think an example would clear it up better
a={-5,-3,0,1,-3} the result would be 4 because there are 4 absolute distinct elements in this array.

length would be <=10000, and most importantly it stated that assume that the array is sorted in ascending order
 */
import java.util.HashMap;

public class Dominator {
	private static int dominator(int[] A) {
		int size = A.length;
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		int counter = 0;
		int j = 0;
		if (size < 1)
			return -1;
		for (int i = 0; i < size; i++) {
			if (counter == 0) {
				counter++;
				j = i;
			} else if (A[i] == A[j]) {
				counter++;
			} else {
				counter--;
			}
		}
		return A[j];

		/*
		 * if(map.containsKey(nums[i])) { int occurences = (int)
		 * map.get(nums[i]); occurences++; if(occurences > size / 2) { dominator
		 * = i; break; }
		 * 
		 * map.put(nums[i], occurences); } else { map.put(nums[i], 1); }
		 */
		// }
		// return -1;
	}

	public static void tests() {
		int[] A = {};
		Assert.assertEquals(dominator(A), 0, "Pusta");
		int[] B = { 0 };
		Assert.assertEquals(dominator(B), 0, "Jeden element");
		int[] C = { 1, 1, 1, 1 };
		Assert.assertEquals(dominator(C), 0, "Ten sam element");
		int[] D = { -5, -3, 0, 1, -3 };
		Assert.assertEquals(dominator(D), -1, "Przyklad 1");
		int[] E = { -5, -6, -5, -5, -5, -5, -3, -3, -5, -5, 1, -5, 6, 7, -5, 8 };
		Assert.assertEquals(dominator(E), 2, "Przyklad 2");
		int[] F = { 1, 1, 1, 1, 2, 1, 1, 1, 5, 1, 1, 5, 5, 5, 5, 5, 5, 5, 1 };
		Assert.assertEquals(dominator(F), 2, "Przyklad 2");
		int[] G = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3 };
		Assert.assertEquals(dominator(G), 2, "Przyklad 3");
	}
}