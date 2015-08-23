import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int numTest = Integer.parseInt(cin.nextLine().trim());
		for (int i = 0; i < numTest; i++) {
			int numFarmer = Integer.parseInt(cin.nextLine().trim());
			int total = 0;
			for (int j = 0; j < numFarmer; j++) {
				StringTokenizer st = new StringTokenizer(cin.nextLine().trim());
				int size = Integer.parseInt(st.nextToken());
				st.nextToken();
				int friend = Integer.parseInt(st.nextToken());
				total += size * friend;
			}
			System.out.println(total);
		}
	}
}
