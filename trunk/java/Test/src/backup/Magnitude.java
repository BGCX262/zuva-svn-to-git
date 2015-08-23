package backup;
/*A magnitude pole of an array A consisting of N integers
 *  is an index K such that all elements with smaller indexes have
 *   values lower or equal to A[K] and all elements with greater
 *    indexes have values greater or equal to A[K], i.e. 
 when  and 
 when K < L < N.
For example, 5 is a magnitude pole of array A such that 
A[0]=4, A[1]=2, A[2]=2, A[3]=3, A[4]=1, A[5]=4, A[6]=7, A[7]=8, A[8]=6, A[9]=9. 
This array doesn'target have any more magnitude poles.

Write a function
class Solution3_BinarySearchError { public int magnitudePole(int[] A); }

that given an array A consisting of N integers returns any of its magnitude poles. 
The function should return -1 if array A doesn'target have any magnitude poles.
Assume that each element of the array is a non-negative integer not exceeding 1,000,000.
For example, given array A such that A[0]=4, A[1]=2, A[2]=2, A[3]=3, A[4]=1, A[5]=4, A[6]=7, A[7]=8, A[8]=6, A[9]=9 
the function should return 5, as explained above.*/

import java.math.BigInteger;

public class Magnitude {
	private static int magnitudePole(int[] A) {
		boolean result;
		for (int i = 0; i < A.length; i++) {
			result = true;
			for (int j = i - 1; j >= 0; j--) {
				if (A[i] < A[j]) {
					result = false;
					break;
				}
			}
			if (result == false) {
				continue;
			}
			for (int j = i + 1; j < A.length; j++) {
				if (A[i] > A[j]) {
					result = false;
					break;
				}
			}
			if (result)
				return i;
		}
		return -1;
	}

	public static void tests() {
		int[] A = {};
		Assert.assertEquals(magnitudePole(A), -1, "Pusta");
		int[] B = { 0 };
		Assert.assertEquals(magnitudePole(B), 0, "Jedno zero");
		int[] C = { 1, 1, 1, 1 };
		Assert.assertEquals(magnitudePole(C), 0, "Ten sam element");
		int[] D = { 4, 2, 2, 3, 1, 4, 7, 8, 6, 9 };
		Assert.assertEquals(magnitudePole(D), 5, "Przyklad 1");
		int[] E = { 2, 1, 4, 2, 3, 1, 3, 5, 2, 7 };
		Assert.assertEquals(magnitudePole(E), 9, "Przyklad 2");
		int[] F = { 2, 1, 5 };
		Assert.assertEquals(magnitudePole(F), 2, "Przyklad 3");
		int[] G = { 2, 3, 1, 2, 1 };
		Assert.assertEquals(magnitudePole(G), -1, "Nieskonczona petla");
		int[] H = { 2 };
		Assert.assertEquals(magnitudePole(H), 0, "Jeden element dodatni");
	}
}