import java.util.Scanner;

/**
 * 567
 */

public class Main {
	static boolean debug = false;
	static int[][] distance = new int[21][21];

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int index = 1;
		while (cin.hasNextInt()) {

			for (int i = 1; i <= 20; i++) {
				for (int j = 1; j <= 20; j++) {
					distance[i][j] = 10000;
				}
				distance[i][i] = 0;
			}
			for (int i = 1; i <= 19; i++) {
				int nNei = cin.nextInt();
				for (int j = 0; j < nNei; j++) {
					int nei = cin.nextInt();
					distance[i][nei] = 1;
					distance[nei][i] = 1;
				}
			}
			// floyd
			for (int k = 1; k <= 20; k++) {
				for (int i = 1; i <= 20; i++) {
					for (int j = 1; j <= 20; j++) {
						distance[i][j] = distance[i][j] < distance[i][k] + distance[k][j] ? distance[i][j] : distance[i][k] + distance[k][j];
					}
				}
			}
			System.out.println("Test Set #" + (index++));
			int nFrom = cin.nextInt();
			for (int i = 0; i < nFrom; i++) {
				int from = cin.nextInt();
				int to = cin.nextInt();
				System.out.format("%2d to %2d:%2d\n", from, to, distance[from][to]);

			}
			System.out.println("");
		}
	}
}
