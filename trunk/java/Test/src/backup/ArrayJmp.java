package backup;
/*
Every element in an array of integers points to a relative 
location from the current element. Precisely, 
if A[k] = m, the jump from k should land at k+A[k]=k+m.
Write a function int arrayJmp(int[] A);
that returns the number of jumps until the pointer jumps 
out of the array when starting from the firstelement.

For example:
A[0]=2, A[1]=3, A[2]=1, A[3]=1, A[4]=3

The pointer's 1st jump is from 0 to 2, 2nd jump from 2 to 3, 
3rd jump from 3 to 4, 4th jump from 4 to 7, but 7 is out of the array.
The number of jumps until the pointer jumps out of the array is 4.

Return -1 if the sequence of jumps never ends.

http://sajha.com/sajha/html/index.cfm?threadid=82940
 */

public class ArrayJmp {
	private static int arrayJmp(int[] A) {
		int len = A.length;
		int counter = 0;
		for (int i = 0; (i > -1 && i < len); counter++, i += A[i]) {
			if (counter > len)
				return -1;
		}
		return counter;
	}

	public static void tests() {
		int[] A = {};
		Assert.assertEquals(arrayJmp(A), 0, "Pusta");
		int[] B = { 0 };
		Assert.assertEquals(arrayJmp(B), -1, "Jedno zero");
		int[] C = { 1, 1, 1, 1 };
		Assert.assertEquals(arrayJmp(C), 4, "Ten sam element");
		int[] D = { 2, 3, 1, 1, 3 };
		Assert.assertEquals(arrayJmp(D), 4, "Przyklad 1");
		int[] E = { 2, 1, 4, 2, 3, -1, -3, 5, 2, 7 };
		Assert.assertEquals(arrayJmp(E), 7, "Przyklad 2");
		int[] F = { 2, 1, -5 };
		Assert.assertEquals(arrayJmp(F), 2, "Przyklad 3");
		int[] G = { 2, 3, -1, -2, -1 };
		Assert.assertEquals(arrayJmp(G), -1, "Nieskonczona petla");
		int[] H = { 2 };
		Assert.assertEquals(arrayJmp(H), 1, "Jeden element dodatni");
		int[] I = { -2 };
		Assert.assertEquals(arrayJmp(I), 1, "Jeden element ujemny");
		int[] J = { 3, 0, 0, 4, 0, 4, 2, 4, -3, 3, 0, -5, 3, 5, 0, -2 };
		Assert.assertEquals(arrayJmp(J), 11, "Przyklad 4");
	}
}