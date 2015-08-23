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
 * 548 uva how to build a tree by inorder and postorder sequence
 * http://anandtechblog
 * .blogspot.co.nz/2011/06/construct-given-tree-from-inorder-and.html
 */
public class Main {
	public static boolean debug = false;
	public static List<Integer> inOrder = new ArrayList<Integer>(), postOrder = new ArrayList<Integer>();
	public static int minDep, minLeafValue;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNext()) {
			minDep = Integer.MAX_VALUE;
			minLeafValue = Integer.MAX_VALUE;
			inOrder.clear();
			postOrder.clear();
			String line = cin.nextLine().trim();
			StringTokenizer st = new StringTokenizer(line);
			while (st.hasMoreTokens()) {
				inOrder.add(Integer.parseInt(st.nextToken()));
			}
			line = cin.nextLine().trim();
			st = new StringTokenizer(line);
			while (st.hasMoreTokens()) {
				postOrder.add(Integer.parseInt(st.nextToken()));
			}
			visitNode(0, postOrder.size() - 1, 0);
			System.out.println(minLeafValue);
		}
	}

	private static void visitNode(int left, int right, int parentDep) {
		if (left > right)
			return;

		int value = postOrder.get(postOrder.size() - 1);
		postOrder.remove(postOrder.size() - 1);
		int depth = parentDep + value;

		if (left == right) {
			if (depth < minDep) {
				minDep = depth;
				minLeafValue = value;
			} else if (depth == minDep) {
				if (value < minLeafValue) {
					minLeafValue = value;
				}
			}
			return;
		}

		int index = inOrder.lastIndexOf(value);
		visitNode(index + 1, right, depth);
		visitNode(left, index - 1, depth);
	}
}
