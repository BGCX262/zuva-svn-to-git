import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

/**
 * 10250 uva from http://www.questtosolve.com/browse.php?pid=10250
 */
public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			StringTokenizer st = new StringTokenizer(line);
			Double x1 = new Double(st.nextToken());
			Double y1 = new Double(st.nextToken());
			Double x2 = new Double(st.nextToken());
			Double y2 = new Double(st.nextToken());
			Double mx = (x1 + x2) / 2;
			Double my = (y1 + y2) / 2;
			Double dx = mx - x1;
			Double dy = my - y1;
			Double x3 = mx - dy;
			Double y3 = my + dx;
			Double x4 = mx + dy;
			Double y4 = my - dx;
			System.out.printf("%.10f %.10f %.10f %.10f\n", x3, y3, x4, y4);
		}
	}
}
