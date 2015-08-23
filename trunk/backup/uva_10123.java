import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.StringTokenizer;
import java.util.TreeSet;

class Obj implements Comparable<Obj> {
	int pos;
	int wei;

	@Override
	public int compareTo(Obj o) {
		if (this.pos < 0)
			return (-this.pos * 2 - 3) * this.wei - ((-o.pos * 2 - 3) * o.wei);
		else
			return (this.pos * 2 - 3) * this.wei - ((o.pos * 2 - 3) * o.wei);
	}

	public String toString() {
		return " pos " + pos + " wei " + wei;
	}
}

/**
 * uva 10123
 * 
 * @author george.dou
 * 
 */
public class Main {
	static List<Obj> board, left, right;
	static int num, boardLength, boardWeight;
	static boolean debug = false, found = false;;

	static boolean balance(int l, int r) {
		int lsum = 0, rsum = 0;
		int i;
		for (i = 0; i < l; i++) {
			lsum += (-left.get(i).pos * 2 - 3) * left.get(i).wei;
		}
		for (i = 0; i < r; i++) {
			rsum += (right.get(i).pos * 2 + 3) * right.get(i).wei;
		}
		rsum += (boardWeight * 3);
		if (lsum > rsum)
			return false;
		lsum = 0;
		rsum = 0;
		for (i = 0; i < l; i++) {
			lsum += (-left.get(i).pos * 2 + 3) * left.get(i).wei;
		}
		for (i = 0; i < r; i++) {
			rsum += (right.get(i).pos * 2 - 3) * right.get(i).wei;
		}
		lsum += (boardWeight * 3);
		if (rsum > lsum)
			return false;
		return true;
	}

	static void dfs(int cur, int l, int r) {
		if (cur == num) {
			for (int i = num - 1; i >= 0; i--) {
				System.out.println(board.get(i).pos + " " + board.get(i).wei);
			}
			found = true;
			return;
		}
		for (int i = l; i < left.size(); i++) {
			if (balance(i, r) && !found) {
				board.set(cur, left.get(i));
				dfs(cur + 1, i + 1, r);
			} else {
				break;
			}
		}
		for (int i = r; i < right.size(); i++) {
			if (balance(l, i) && !found) {
				board.set(cur, right.get(i));
				dfs(cur + 1, l, i + 1);
			} else {
				break;
			}
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int caseNum = 0;
		if (args.length > 0)
			debug = true;
		for (;;) {
			caseNum++;
			String line = cin.nextLine();
			StringTokenizer st = new StringTokenizer(line);
			boardLength = Integer.parseInt(st.nextToken());
			boardWeight = Integer.parseInt(st.nextToken());
			num = Integer.parseInt(st.nextToken());
			if (boardLength == 0 && boardWeight == 0 && num == 0)
				break;

			left = new ArrayList<Obj>();
			right = new ArrayList<Obj>();
			board = new ArrayList<Obj>(30);
			for (int i = 0; i < 30; i++) {
				board.add(null);
			}
			found = false;
			for (int i = 0; i < num; i++) {
				line = cin.nextLine();
				st = new StringTokenizer(line);
				Obj obj = new Obj();
				obj.pos = Integer.parseInt(st.nextToken());
				obj.wei = Integer.parseInt(st.nextToken());
				if (obj.pos < 0) {
					left.add(obj);
				} else {
					right.add(obj);
				}
			}
			Collections.sort(left);
			Collections.sort(right);
			System.out.println("Case " + caseNum + ":");
			dfs(0, 0, 0);
			if (!found) {
				System.out.println("Impossible");
			}
		}
	}
}