import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			int n = Integer.parseInt(line);
			if (n == 0)
				break;
			int k = (int) Math.ceil(Math.sqrt(new Double(n).doubleValue()));
			int mid, x, y;
			if (k % 2 == 0) {
				mid = k * k - k + 1;
				if (n >= mid) {
					x = k;
					y = k - (n - mid);
				} else {
					x = k - (mid - n);
					y = k;
				}
			} else {
				mid = (k - 1) * (k - 1) + 1 + k - 1;
				if (n >= mid) {
					x = k - (n - mid);
					y = k;
				} else {
					x = k;
					y = k - (mid - n);
				}
			}
			System.out.println(x + " " + y);
		}
	}
}