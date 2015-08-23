import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;
import java.util.StringTokenizer;

/**
 * 10034
 */

class Node {
	double x, y;
	int i;
}

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int testN = Integer.parseInt(cin.nextLine());
		for (int test = 0; test < testN; test++) {
			cin.nextLine();
			ArrayList<Node> minSet = new ArrayList<Node>();
			ArrayList<Node> otherSet = new ArrayList<Node>();
			ArrayList<Node> nodes = new ArrayList<Node>();
			int n = Integer.parseInt(cin.nextLine());
			double[][] dist = new double[n][n];
			for (int i = 0; i < n; i++) {
				Node node = new Node();
				StringTokenizer st = new StringTokenizer(cin.nextLine());
				node.x = Double.parseDouble(st.nextToken());
				node.y = Double.parseDouble(st.nextToken());
				node.i = i;
				nodes.add(node);
				if (i == 0) {
					minSet.add(node);
				} else {
					otherSet.add(node);
				}
			}
			for (int i = 0; i < n - 1; i++) {
				for (int j = i + 1; j < n; j++) {
					double t1 = nodes.get(i).x - nodes.get(j).x;
					double t2 = nodes.get(i).y - nodes.get(j).y;
					dist[i][j] = dist[j][i] = t1 * t1 + t2 * t2;
				}
			}

			double allDist = 0;
			while (otherSet.size() > 0) {
				double minDist = dist[otherSet.get(0).i][minSet.get(0).i];
				Node minOtherNode = otherSet.get(0);
				Node minNode = minSet.get(0);
				for (Node o : otherSet) {
					for (Node m : minSet) {
						if (dist[o.i][m.i] < minDist) {
							minDist = dist[o.i][m.i];
							minNode = m;
							minOtherNode = o;
						}
					}
				}
				otherSet.remove(minOtherNode);
				minSet.add(minOtherNode);
				allDist += Math.sqrt(dist[minNode.i][minOtherNode.i]);
			}

			if (Main.debug) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						System.out.print(dist[i][j] + " ");
					}
					System.out.println(" ");
				}
			}
			if (test != 0) {
				System.out.println("");
			}
			System.out.format("%.2f\n", allDist);
		}
	}
}