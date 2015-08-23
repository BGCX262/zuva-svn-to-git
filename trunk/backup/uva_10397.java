import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 10397
 */

class Node {
	int x, y;

	public String toString() {
		return " x " + x + " y " + y;
	}
}

class Link implements Comparable<Link> {
	int n1, n2;
	double wei;

	public Link(int i, int j, double sqrt) {
		this.n1 = i;
		this.n2 = j;
		this.wei = sqrt;
	}

	public int compareTo(Link o) {
		if (this.wei < o.wei) {
			return -1;
		} else if (this.wei > o.wei) {
			return 1;
		}
		return 0;
	}
}

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNext()) {
			ArrayList<Node> nodes = new ArrayList<Node>();
			int numNode = cin.nextInt();
			nodes.add(null);
			for (int i = 1; i <= numNode; i++) {
				Node n = new Node();
				n.x = cin.nextInt();
				n.y = cin.nextInt();
				nodes.add(n);
			}

			Link[][] allLink = new Link[numNode + 1][numNode + 1];
			ArrayList<Link> sortLink = new ArrayList<Link>();
			for (int i = 1; i < numNode; i++) {
				for (int j = i + 1; j <= numNode; j++) {
					Link l = new Link(i, j, Math.sqrt(Math.pow(nodes.get(i).x - nodes.get(j).x, 2) + Math.pow(nodes.get(i).y - nodes.get(j).y, 2)));
					allLink[i][j] = l;
					sortLink.add(l);
				}
			}
			int numEdge = cin.nextInt();
			for (int i = 0; i < numEdge; i++) {
				int n1 = cin.nextInt();
				int n2 = cin.nextInt();
				if (n1 > n2) {
					int t = n1;
					n1 = n2;
					n2 = t;
				}
				allLink[n1][n2].wei = 0;
			}

			// Kruskal
			Collections.sort(sortLink);

			double distAll = 0;
			int[] connect = new int[numNode + 1];
			for (int i = 1; i <= numNode; i++) {
				connect[i] = i;
			}
			for (Link link : sortLink) {
				int con1 = find(connect, link.n1);
				int con2 = find(connect, link.n2);
				if (con1 != con2) {
					connect[con1] = con2;
					distAll += link.wei;
				}
			}
			System.out.format("%.2f\n", distAll);
		}
	}

	private static int find(int[] connect, int n1) {
		if (connect[n1] == n1)
			return n1;
		connect[n1] = find(connect, connect[n1]);
		return connect[n1];
	}
}

//
//
//
//
// class Node {
// int x, y, graphI, nodeI;
// ArrayList<Node> nei = new ArrayList<Node>();
//
// public String toString() {
// return " x " + x + " y " + y + " graph " + graphI + " nodeI " + nodeI;
// }
// }
//
// public class Main {
// static boolean debug = false;
//
// public static void main(String[] args) {
// Scanner cin = new Scanner(System.in);
// if (args.length > 0)
// debug = true;
// while (cin.hasNextLine()) {
// StringTokenizer st = new StringTokenizer(cin.nextLine());
// ArrayList<Node> nodes = new ArrayList<Node>();
// ArrayList<ArrayList<Node>> graph = new ArrayList<ArrayList<Node>>();
// int numNode = Integer.parseInt(st.nextToken());
// nodes.add(null);
// for (int i = 1; i <= numNode; i++) {
// st = new StringTokenizer(cin.nextLine());
// int x = Integer.parseInt(st.nextToken());
// int y = Integer.parseInt(st.nextToken());
// Node n = new Node();
// n.x = x;
// n.y = y;
// n.graphI = -1;
// n.nodeI = i;
// nodes.add(n);
// }
//
// double[][] dist = new double[numNode + 1][numNode + 1];
// for (int i = 1; i < numNode; i++) {
// for (int j = i + 1; j <= numNode; j++) {
// int t1 = (nodes.get(i).x - nodes.get(j).x);
// int t2 = (nodes.get(i).y - nodes.get(j).y);
// dist[i][j] = dist[j][i] = Math.sqrt(Math.pow(t1, 2) + Math.pow(t2, 2));
// }
// }
//
// st = new StringTokenizer(cin.nextLine());
//
// int numEdge = Integer.parseInt(st.nextToken());
// for (int i = 0; i < numEdge; i++) {
// st = new StringTokenizer(cin.nextLine());
// int n1 = Integer.parseInt(st.nextToken());
// int n2 = Integer.parseInt(st.nextToken());
// nodes.get(n1).nei.add(nodes.get(n2));
// nodes.get(n2).nei.add(nodes.get(n1));
// }
//
// int graphI = 0;
// for (int i = 1; i < nodes.size(); i++) {
// if (nodes.get(i).graphI == -1) {
// ArrayList<Node> subGraph = new ArrayList<Node>();
// dfs(subGraph, nodes.get(i), graphI++);
// graph.add(subGraph);
// }
// }
//
// if (Main.debug) {
// for (int i = 0; i < graph.size(); i++) {
// ArrayList<Node> sub = graph.get(i);
// System.out.print("graphI " + i + " ");
// for (Node n : sub) {
// System.out.print(" [" + n.toString() + "], ");
// }
// System.out.print("\n");
// }
// }
//
// double distAll = 0;
// for (;;) {
// if (graph.size() == 1)
// break;
// double minDist = dist[graph.get(0).get(0).nodeI][graph.get(1).get(0).nodeI];
// int minGraphI = 1;
// for (int i = 1; i < graph.size(); i++) {
// double temp = min(dist, graph.get(0), graph.get(i));
// if (temp < minDist) {
// minDist = temp;
// minGraphI = i;
// }
// }
// distAll += minDist;
// graph.get(0).addAll(graph.get(minGraphI));
// graph.remove(minGraphI);
// }
// System.out.format("%.2f\n", distAll);
// }
// }
//
// private static double min(double[][] dist, ArrayList<Node> g1,
// ArrayList<Node> g2) {
// double minDist = dist[g1.get(0).nodeI][g2.get(0).nodeI];
// for (int i = 0; i < g1.size(); i++) {
// for (int j = 0; j < g2.size(); j++) {
// double temp = dist[g1.get(i).nodeI][g2.get(j).nodeI];
// if (temp < minDist) {
// minDist = temp;
// }
// }
// }
// return minDist;
// }
//
// private static void dfs(ArrayList<Node> subGraph, Node n, int gI) {
// n.graphI = gI;
// subGraph.add(n);
// for (Node nei : n.nei) {
// if (nei.graphI == -1) {
// dfs(subGraph, nei, gI);
// }
// }
// }
// }

// class Node {
// int x, y, graphI, nodeI;
//
// public String toString() {
// return " x " + x + " y " + y + " graph " + graphI + " nodeI " + nodeI;
// }
// }
//
// public class Main {
// static boolean debug = false;
//
// public static void main(String[] args) {
// Scanner cin = new Scanner(System.in);
// if (args.length > 0)
// debug = true;
// while (cin.hasNextLine()) {
// StringTokenizer st = new StringTokenizer(cin.nextLine());
// ArrayList<Node> nodes = new ArrayList<Node>();
// ArrayList<ArrayList<Node>> graph = new ArrayList<ArrayList<Node>>();
// int numNode = Integer.parseInt(st.nextToken());
// nodes.add(null);
// for (int i = 1; i <= numNode; i++) {
// st = new StringTokenizer(cin.nextLine());
// int x = Integer.parseInt(st.nextToken());
// int y = Integer.parseInt(st.nextToken());
// Node n = new Node();
// n.x = x;
// n.y = y;
// n.graphI = -1;
// n.nodeI = i;
// nodes.add(n);
// }
//
// double[][] dist = new double[numNode + 1][numNode + 1];
// int[][] connected = new int[numNode + 1][numNode + 1];
// for (int i = 1; i < numNode; i++) {
// for (int j = i + 1; j <= numNode; j++) {
// int t1 = (nodes.get(i).x - nodes.get(j).x);
// int t2 = (nodes.get(i).y - nodes.get(j).y);
// dist[i][j] = dist[j][i] = Math.sqrt(Math.pow(t1, 2) + Math.pow(t2, 2));
// }
// }
//
// if (Main.debug) {
// for (int i = 1; i <= numNode; i++) {
// for (int j = 1; j <= numNode; j++) {
// System.out.print(dist[i][j] + ",");
// }
// System.out.print("\n");
// }
// }
//
// st = new StringTokenizer(cin.nextLine());
//
// int numEdge = Integer.parseInt(st.nextToken());
// for (int i = 0; i < numEdge; i++) {
// st = new StringTokenizer(cin.nextLine());
// int n1 = Integer.parseInt(st.nextToken());
// int n2 = Integer.parseInt(st.nextToken());
// connected[n1][n2] = 1;
// connected[n2][n1] = 1;
// }
//
// int graphI = 0;
// for (int i = 1; i < nodes.size(); i++) {
// if (nodes.get(i).graphI == -1) {
// ArrayList<Node> subGraph = new ArrayList<Node>();
// dfs(nodes, connected, numNode, subGraph, nodes.get(i), graphI++);
// graph.add(subGraph);
// }
// }
//
// if (Main.debug) {
// for (int i = 0; i < graph.size(); i++) {
// ArrayList<Node> sub = graph.get(i);
// System.out.print("graphI " + i + " ");
// for (Node n : sub) {
// System.out.print(" [" + n.toString() + "], ");
// }
// System.out.print("\n");
// }
// }
//
// double distAll = 0;
// for (;;) {
// if (graph.size() == 1)
// break;
// double minDist = dist[graph.get(0).get(0).nodeI][graph.get(1).get(0).nodeI];
// int minGraphI = 1;
// for (int i = 1; i < graph.size(); i++) {
// double temp = min(dist, graph.get(0), graph.get(i));
// if (temp < minDist) {
// minDist = temp;
// minGraphI = i;
// }
// }
//
// if (Main.debug) {
// System.out.println("minDist " + minDist);
// }
//
// distAll += minDist;
// graph.get(0).addAll(graph.get(minGraphI));
// graph.remove(minGraphI);
// }
// System.out.format("%.2f\n", distAll);
// }
// }
//
// private static double min(double[][] dist, ArrayList<Node> g1,
// ArrayList<Node> g2) {
// double minDist = dist[g1.get(0).nodeI][g2.get(0).nodeI];
// for (int i = 0; i < g1.size(); i++) {
// for (int j = 0; j < g2.size(); j++) {
// double temp = dist[g1.get(i).nodeI][g2.get(j).nodeI];
// if (temp < minDist) {
// minDist = temp;
// }
// }
// }
// return minDist;
// }
//
// private static void dfs(ArrayList<Node> nodes, int[][] connected, int
// numNode, ArrayList<Node> subGraph, Node n, int gI) {
// n.graphI = gI;
// subGraph.add(n);
// for (int i = 1; i <= numNode; i++) {
// if (connected[n.nodeI][i] == 1 && nodes.get(i).graphI == -1) {
// dfs(nodes, connected, numNode, subGraph, nodes.get(i), gI);
// }
// }
//
// }
// }