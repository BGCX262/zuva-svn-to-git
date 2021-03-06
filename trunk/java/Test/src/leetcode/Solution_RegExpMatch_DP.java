package leetcode;
public class Solution_RegExpMatch_DP {
	public boolean isMatch(String s, String p) {
		if (s == null && p == null)
			return true;

		if (s.length() == 0 && p.length() == 0)
			return true;

		boolean[][] matrix = new boolean[s.length() + 1][p.length() + 1];

		matrix[0][0] = true;

		for (int i = 1; i <= s.length(); i++)
			matrix[i][0] = false;

		for (int j = 1; j <= p.length(); j++) {
			char currReg = p.charAt(j - 1);
			if (currReg == '*' && j > 1)
				matrix[0][j] = matrix[0][j - 2];
			else
				matrix[0][j] = false;

		}

		for (int i = 1; i <= s.length(); i++)
			for (int j = 1; j <= p.length(); j++) {
				char currReg = p.charAt(j - 1);
				char currChar = s.charAt(i - 1);

				if (currReg == currChar || currReg == '.')
					matrix[i][j] = matrix[i - 1][j - 1];

				else if (currReg == '*' && j > 1) {
					char prevReg = p.charAt(j - 2);
					if (prevReg == currChar || prevReg == '.')
						matrix[i][j] = matrix[i - 1][j] || matrix[i][j - 2] || matrix[i][j - 1];
					// matrix[i-1][j]:abb vs ab*: depends on ab vs ab*
					// matrix[i][j-2] a vs ab* depends on a vs a
					// matrix[i][j-1] ab vs ab*: depends on ab vs ab
					else
						matrix[i][j] = matrix[i][j - 2];
				}

				else {
					matrix[i][j] = false;
				}
			}
		return matrix[s.length()][p.length()];
	}

	public static void main(String[] args) {
		Solution_RegExpMatch_DP solution_RegExpMatch_DP = new Solution_RegExpMatch_DP();
		System.out.println(solution_RegExpMatch_DP.isMatch("", ""));
	}

}
