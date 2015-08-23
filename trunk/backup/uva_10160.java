import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.StringTokenizer;
import java.util.TreeSet;

/**
 * uva 10160
 * 
 * @author george.dou
 * 
 */
public class Main {
	static long[] allFlag, allLaterFlag;
	static long allCoverFlag, ONE = 1l;
	static int numTown, numConn, minBuild;
	static boolean debug = false;

	static void dfs(int cur, long flag, int buildNum) {
		if (Main.debug) {
			System.out.println("cur " + cur + " buildNum " + buildNum + " minBuild " + minBuild);
			System.out.println("flag " + flag + " allCoverFlag " + allCoverFlag + " allFlag " + allFlag[cur]);
		}

		if (buildNum >= minBuild) {
			return;
		}
		if (flag == allCoverFlag) {
			if (buildNum < minBuild) {
				minBuild = buildNum;
			}
			return;
		}
		for (int i = cur + 1; i <= numTown; i++) {
			if (Main.debug) {
				System.out.println("allFlag[" + i + "] " + allFlag[i] + " allLaterFlag[" + i + "] " + allLaterFlag[i]);
			}
			if (flag == (flag | allFlag[i]))
				continue;
			if ((flag | allLaterFlag[i]) != allCoverFlag)
				break;
			dfs(i, flag | allFlag[i], buildNum + 1);
		}
		return;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		for (;;) {
			String line = cin.nextLine();
			StringTokenizer st = new StringTokenizer(line);
			numTown = Integer.parseInt(st.nextToken());
			numConn = Integer.parseInt(st.nextToken());
			if (numTown == 0 && numConn == 0)
				break;
			allCoverFlag = (ONE << numTown) - 1;
			allFlag = new long[36];
			allLaterFlag = new long[36];
			for (int i = 1; i <= 35; i++) {
				allFlag[i] = (ONE << (i - 1));
			}

			minBuild = numTown;
			for (int i = 0; i < numConn; i++) {
				line = cin.nextLine();
				st = new StringTokenizer(line);
				int num1 = Integer.parseInt(st.nextToken());
				int num2 = Integer.parseInt(st.nextToken());
				allFlag[num1] |= ONE << (num2 - 1);
				allFlag[num2] |= ONE << (num1 - 1);
			}
			allLaterFlag[numTown] = allFlag[numTown];
			for (int i = numTown - 1; i >= 1; i--) {
				allLaterFlag[i] = (allLaterFlag[i + 1] | allFlag[i]);
			}
			for (int i = 1; i <= numTown; i++)
				dfs(i, allFlag[i], 1);
			System.out.println(minBuild);
		}
	}
}