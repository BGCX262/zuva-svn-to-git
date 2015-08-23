package backup;
import java.util.Iterator;
import java.util.SortedSet;
import java.util.TreeSet;

public class CheckPermutation {
	public static int solution(int A[]) {
		if (A.length == 0) {
			return 0;
		}

		SortedSet<Integer> set = new TreeSet<Integer>();
		for (int i = 0; i < A.length; i++) {
			set.add(A[i]);
		}

		Iterator<Integer> it = set.iterator();
		long counter = 1;
		while (it.hasNext()) {
			if (counter != it.next()) {
				return 0;
			}
			counter++;
		}

		return 1;
	}

}
