package backup;
/*
Write a function

int nesting(string S);

which given a string S made of characters ( and ) returns 1if S is properly nested, 0 otherwise.
In precise terms, a string is propetly nested if it has one of the following forms:
empty,
(S), where S is properly nested,
ST, where both S and T are properly nested.

For example, given the string
(()(())())
your function should return 1, and for the string
())
your function should return 0.
 */

public class Nesting {
	private static int nesting(String s) {
		int counter = 0;
		if (s != null && s.length() > 0) {
			char[] charArr = s.toCharArray();
			for (char ch : charArr) {
				if (ch == '(') {
					counter++;
				} else if (ch == ')') {
					counter--;
				}
				if (counter < 0)
					break;
			}
			if (counter == 0)
				return 1;

		}

		return 0;
	}

	public static void tests() {
		Assert.assertEquals(nesting(""), 0, "Pusty");
		Assert.assertEquals(nesting("()"), 1, "Przyklad 1 - dobry");
		Assert.assertEquals(nesting("(()()(()))"), 1, "Przyklad 2 - dobry");
		Assert.assertEquals(nesting("((()(()))"), 0, "Przyklad 3 - zly");
		Assert.assertEquals(nesting("((()(()"), 0, "Przyklad 4 - zly");
		Assert.assertEquals(nesting("(((A)C(())"), 0, "Przyklad 5 - zly");
		Assert.assertEquals(nesting("(A)C(()))C)"), 0, "Przyklad 6 - zly");
		Assert.assertEquals(nesting("AC"), 1, "Przyklad 6 - dobry");
	}
}