package backup;
import java.util.ArrayList;
import java.util.List;

public class Ps {
	public static int ps(int[] A) {
		if (A.length == 0 || A.length == 1)
			return 0;

		List<Integer> seen = new ArrayList<Integer>();

		for (int i = 0; i < A.length; i++) {
			if (!seen.contains(A[i]))
				seen.add(A[i]);
		}
		for (int i = 0; i < A.length; i++) {
			if (seen.contains(A[i]))
				seen.remove(seen.indexOf(A[i]));
			if (seen.size() == 0)
				return i;
		}

		return 0;
	}

	public static void tests() {
		int[] A = { 2, 3, 45, 56, 1, 2, 4, 4, 6 };
		Assert.assertEquals(ps(A), 8, "Zwykly");

		int[] B = {};
		Assert.assertEquals(ps(B), 0, "Pusta");

		int[] C = { 1 };
		Assert.assertEquals(ps(C), 0, "Jeden element");

		int[] D = { 1, 1, 1, 1, 1, 1 };
		Assert.assertEquals(ps(D), 0, "Ten sam element");

		int[] E = { 1, 2, 1, 2, 1, 2 };
		Assert.assertEquals(ps(E), 1, "Dwa rozne");

	}
}
