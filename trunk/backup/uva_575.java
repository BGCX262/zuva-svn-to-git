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
			if (line.trim().equals("0"))
				break;
			long r = 0;
			for (int i = 0; i < line.length(); i++) {
				int n = Integer.parseInt(new Character(line.charAt(i)).toString());
				switch (n) {
				case 0:
					break;
				case 1:
					r += ((1 << (line.length() - i)) - 1);
					break;
				case 2:
					r += 2 * ((1 << (line.length() - i)) - 1);
					break;
				}
				if (debug) {
					System.out.println("i:" + i + ", r:" + r);
				}

			}
			System.out.println(r);
		}
	}
}
