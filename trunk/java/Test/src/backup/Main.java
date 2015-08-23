package backup;
import java.util.*;

/**
 * Given an array A of N integers, we draw N discs in a 2D plane such that the
 * I-th disc is centered on (0,I) and has a radius of A[I]. We say that the J-th
 * disc and K-th disc intersect if J ≠ K and J-th and K-th discs have at least
 * one common point. Write a function: class Solution3_BinarySearchError { public int
 * number_of_disc_intersections(int[] A); } that, given an array A describing N
 * discs as explained above, returns the number of pairs of intersecting discs.
 * 
 */
class Main {
	public static void main(String[] args) {
		List<Marker> l = new ArrayList<Marker>();

		l.add(new Marker(0, true));
		l.add(new Marker(10, false));

		l.add(new Marker(5, true));
		l.add(new Marker(20, false));

		l.add(new Marker(2, true));
		l.add(new Marker(30, false));

		Collections.sort(l);
		int total = -1, overlaps = 0;
		for (int i = 0; i < l.size(); i++) {
			if (l.get(i).green) {
				total++;
				if (total > 0)
					overlaps += total;
			} else {
				total--;
			}
		}
		System.out.println(overlaps);
	}
}

class Marker implements Comparable<Marker> {
	int n;
	boolean green;

	public Marker(int a, boolean b) {
		n = a;
		green = b;
	}

	public int compareTo(Marker other) {
		return n < other.n ? -1 : (n > other.n ? 1 : (green ? -1 : 1));
	}
}