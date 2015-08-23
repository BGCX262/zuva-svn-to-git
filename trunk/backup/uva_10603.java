import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;

class Node {
	int[] jugs = new int[3];
	int poured;

	Node newNode() {
		Node newNode = new Node();
		newNode.jugs[0] = this.jugs[0];
		newNode.jugs[1] = this.jugs[1];
		newNode.jugs[2] = this.jugs[2];
		newNode.poured = this.poured;
		return newNode;
	}

	public String toString() {
		return jugs[0] + "/" + Main.liters[0] + " " + jugs[1] + "/" + Main.liters[1] + " " + jugs[2] + "/" + Main.liters[2] + " poured " + poured;
	}
}

/**
 * uva 10603
 */
public class Main {
	static int[] liters = new int[3];;
	static int d, dClose, minPouredClose;
	static boolean debug = false;
	static Node best[][];

	static void bfs() {
		Stack<Node> stack = new Stack<Node>();
		Node n = new Node();
		n.jugs[0] = 0;
		n.jugs[1] = 0;
		n.jugs[2] = liters[2];
		n.poured = 0;
		best[n.jugs[0]][n.jugs[1]] = n;

		stack.push(n);
		while (!stack.empty()) {
			Node cur = stack.pop();
			for (int i = 0; i < 3; i++) {
				if (cur.jugs[i] == d) {
					if (dClose == d && cur.poured < minPouredClose)
						minPouredClose = cur.poured;
					else if (dClose != d) {
						dClose = d;
						minPouredClose = cur.poured;
					}
				} else if ((cur.jugs[i] > dClose && cur.jugs[i] < d) || (cur.jugs[i] == dClose && cur.poured < minPouredClose)) {
					dClose = cur.jugs[i];
					minPouredClose = cur.poured;
				}
				for (int j = 0; j < 3; j++) {
					int pour = liters[j] - cur.jugs[j];
					if (i != j && cur.jugs[i] > 0 && pour > 0) {
						if (pour > cur.jugs[i]) {
							pour = cur.jugs[i];
						}
						Node newNode = cur.newNode();
						newNode.jugs[j] += pour;
						newNode.jugs[i] -= pour;
						newNode.poured += pour;
						if (best[newNode.jugs[0]][newNode.jugs[1]] == null || best[newNode.jugs[0]][newNode.jugs[1]].poured > newNode.poured) {
							best[newNode.jugs[0]][newNode.jugs[1]] = newNode;
							stack.push(newNode);
						}
					}
				}
			}
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
		String line = cin.nextLine();
		int numTest = Integer.parseInt(line);
		for (int k = 0; k < numTest; k++) {
			line = cin.nextLine();
			StringTokenizer st = new StringTokenizer(line);
			liters[0] = Integer.parseInt(st.nextToken());
			liters[1] = Integer.parseInt(st.nextToken());
			liters[2] = Integer.parseInt(st.nextToken());
			d = Integer.parseInt(st.nextToken());
			dClose = 0;
			minPouredClose = 0;
			best = new Node[201][201];
			bfs();
			System.out.println(minPouredClose + " " + dClose);
		}
	}
}