import java.util.ArrayList;
import java.util.Collections;
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

class Node {
	int[][] states;
	String move;
	int key;
	int zeroX, zeroY;

	Node(int[][] s, String m, int x, int y) {
		this.states = new int[3][3];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this.states[i][j] = s[i][j];
			}
		}
		this.move = m;
		this.zeroX = x;
		this.zeroY = y;
	}

	void calKey() {
		StringBuffer r = new StringBuffer();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				r.append(states[i][j]);
			}
		}
		key = Integer.parseInt(r.toString());
	}

	Node move(char c) {
		Node r = null;
		switch (c) {
		case 'U':
			if (this.zeroX > 0) {
				r = new Node(this.states, this.move.toString(), this.zeroX, this.zeroY);
				int t = r.states[r.zeroX - 1][r.zeroY];
				r.states[r.zeroX - 1][r.zeroY] = 0;
				r.states[r.zeroX][r.zeroY] = t;
				r.move += "U";
				r.zeroX--;
				r.calKey();
			}
			break;
		case 'D':
			if (this.zeroX < 2) {
				r = new Node(this.states, this.move.toString(), this.zeroX, this.zeroY);
				int t = r.states[r.zeroX + 1][r.zeroY];
				r.states[r.zeroX + 1][r.zeroY] = 0;
				r.states[r.zeroX][r.zeroY] = t;
				r.move += "D";
				r.zeroX++;
				r.calKey();
			}
			break;
		case 'L':
			if (this.zeroY > 0) {
				r = new Node(this.states, this.move.toString(), this.zeroX, this.zeroY);
				int t = r.states[r.zeroX][r.zeroY - 1];
				r.states[r.zeroX][r.zeroY - 1] = 0;
				r.states[r.zeroX][r.zeroY] = t;
				r.move += "L";
				r.zeroY--;
				r.calKey();
			}
			break;
		case 'R':
			if (this.zeroY < 2) {
				r = new Node(this.states, this.move.toString(), this.zeroX, this.zeroY);
				int t = r.states[r.zeroX][r.zeroY + 1];
				r.states[r.zeroX][r.zeroY + 1] = 0;
				r.states[r.zeroX][r.zeroY] = t;
				r.move += "R";
				r.zeroY++;
				r.calKey();
			}
			break;
		}
		return r;
	}

	public String toString() {
		String r = "";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				r += this.states[i][j] + " ";
			}
			r += "\n";
		}
		r += this.move;
		return r;
	}

}

/**
 * uva 10085
 */
public class Main {
	static Node best;
	static boolean debug = false;

	static void bfs(Node init) {
		char [] moveCmd = {'D','U','R','L'};
		Queue<Node> queue = new LinkedList<Node>();
		HashSet<Integer> visited = new HashSet<Integer>();
		queue.add(init);
		init.calKey();
		visited.add(init.key);
		best = init;
		while (!queue.isEmpty()) {
			Node cur = queue.poll();
			if (cur.move.length() > best.move.length()) {
				best = cur;
			}
			if (Main.debug) {
				System.out.println(cur.toString());
			}
			for(int i=0;i<4;i++){
				Node newNode = cur.move(moveCmd[i]);
				if (newNode != null && !visited.contains(newNode.key)) {
					queue.add(newNode);
					visited.add(newNode.key);
				}	
			}
		}
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
		cin.nextLine();
		for (int k = 0; k < numTest; k++) {
			int[][] initialState = new int[3][3];
			int x = 0, y = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					initialState[i][j] = cin.nextInt();
					if (initialState[i][j] == 0) {
						x = i;
						y = j;
					}
				}
			}
			bfs(new Node(initialState, "", x, y));
			System.out.println("Puzzle #" + (k + 1));
			System.out.println(best.states[0][0] + " " + best.states[0][1] + " " + best.states[0][2]);
			System.out.println(best.states[1][0] + " " + best.states[1][1] + " " + best.states[1][2]);
			System.out.println(best.states[2][0] + " " + best.states[2][1] + " " + best.states[2][2]);
			System.out.println(best.move);
		}
	}
}