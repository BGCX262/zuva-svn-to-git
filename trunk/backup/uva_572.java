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
 * uva 572
 */

class Node {
	int x, y;
	boolean hasVisited = false;
	private List<Node> neighbor = new ArrayList<Node>();

	Node(int r, int c) {
		x = r;
		y = c;
	}

	void addNeighbor(Node n) {
		this.neighbor.add(n);
	}

	List<Node> getNeighbor() {
		return this.neighbor;
	}

	public String toString() {
		return x + ", " + y + " has neighbor " + this.neighbor.size() + ", visited " + hasVisited;
	}
}

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNext()) {
			int num = 0;
			String line = cin.nextLine();
			StringTokenizer st = new StringTokenizer(line);
			int row = Integer.parseInt(st.nextToken());
			int col = Integer.parseInt(st.nextToken());
			if (row == 0)
				break;
			List<Node> all = new ArrayList<Node>();
			Node grid[][] = new Node[row][col];
			for (int i = 0; i < row; i++) {
				line = cin.nextLine();
				for (int j = 0; j < col; j++) {
					if (line.charAt(j) == '@') {
						Node node = new Node(i, j);
						if (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] != null) {
							grid[i - 1][j - 1].addNeighbor(node);
							node.addNeighbor(grid[i - 1][j - 1]);
						}
						if (i - 1 >= 0 && grid[i - 1][j] != null) {
							grid[i - 1][j].addNeighbor(node);
							node.addNeighbor(grid[i - 1][j]);
						}
						if (i - 1 >= 0 && j + 1 < col && grid[i - 1][j + 1] != null) {
							grid[i - 1][j + 1].addNeighbor(node);
							node.addNeighbor(grid[i - 1][j + 1]);
						}
						if (j - 1 >= 0 && grid[i][j - 1] != null) {
							grid[i][j - 1].addNeighbor(node);
							node.addNeighbor(grid[i][j - 1]);
						}
						grid[i][j] = node;
						all.add(node);
					}
				}
			}
			for (Node n : all) {
				if (!n.hasVisited) {
					num++;
					dfs(n);
				}
			}
			System.out.println(num);

			if (debug) {
				System.out.println("" + row + ", " + col);
				for (Node n : all) {
					System.out.println(n);
				}
			}
		}
	}

	private static void dfs(Node node) {
		node.hasVisited = true;
		for (Node neighbor : node.getNeighbor()) {
			if (!neighbor.hasVisited) {
				dfs(neighbor);
			}
		}
	}
}
