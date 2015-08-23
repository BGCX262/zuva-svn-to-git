import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 10189
 */

class Bomb {
	int x, y;

	public String toString() {
		return "Bomb [x " + x + " y " + y + "]";
	}
}

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		
		for (int index = 1;; index++) {
			StringTokenizer st = new StringTokenizer(cin.nextLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			if (n == 0 && m == 0)
				break;
			
			ArrayList<Bomb> bombs = new ArrayList<Bomb>();
			int[][] board = new int[128][128];
			for (int i = 1; i <= n; i++) {
				String line = cin.nextLine();
				for (int j = 1; j <= m; j++) {
					char c = line.charAt(j - 1);
					if (c == '*') {
						board[i][j] = -1;
						Bomb bomb = new Bomb();
						bomb.x = i;
						bomb.y = j;
						bombs.add(bomb);
					} else if (c == '.') {
						board[i][j] = 0;
					}
				}
			}
			
			for (Bomb b : bombs) {
				int x = b.x;
				int y = b.y;
				if (board[x - 1][y - 1] != -1) {
					// left up
					board[x - 1][y - 1]++;
				}
				if (board[x - 1][y] != -1) {
					// up
					board[x - 1][y]++;
				}
				if (board[x - 1][y + 1] != -1) {
					// right up
					board[x - 1][y + 1]++;
				}
				if (board[x][y - 1] != -1) {
					// left
					board[x][y - 1]++;
				}
				if (board[x][y + 1] != -1) {
					// right
					board[x][y + 1]++;
				}
				if (board[x + 1][y - 1] != -1) {
					// left down
					board[x + 1][y - 1]++;
				}
				if (board[x + 1][y] != -1) {
					// down
					board[x + 1][y]++;
				}
				if (board[x + 1][y + 1] != -1) {
					// right down
					board[x + 1][y + 1]++;
				}
			}
			if (index != 1) {
				System.out.print("\n");
			}
			System.out.println("Field #" + index + ":");
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					System.out.print(board[i][j] == -1 ? "*" : board[i][j]);
				}
				System.out.print("\n");
			}
		}
	}
}