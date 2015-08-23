import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

/**
 * uva 1242 , maximum flow, max flow
 * 
 */

public class Main {
	static boolean debug = false;
	static int source = 0, target, nodeSize, edgeSize;
	static int[][] adjMatric = new int[10005][10005];
	static List<Integer>[] adjList = new ArrayList[10005];;

	static int max_flow() {
		int res = 0;
		while (true) {
			int pathCap = findPath();
			if (pathCap == 0)
				break;
			else
				res += pathCap;
		}
		return res;
	}

	static int findPath() {
		Queue<Integer> q = new LinkedList<Integer>();
		boolean[] visited = new boolean[nodeSize + 2];
		q.add(source);
		visited[source] = true;
		int[] path = new int[nodeSize + 2];
		Arrays.fill(path, -1);
		boolean foundTarget = false;
		while (!q.isEmpty()) {
			int curr = q.poll();

			for (int i = 0; i < adjList[curr].size(); i++) {
				int to = adjList[curr].get(i);
				if (adjMatric[curr][to] > 0 && !visited[to]) {
					q.add(to);
					visited[to] = true;
					path[to] = curr;
					if (to == target) {
						foundTarget = true;
						break;
					}
				}
			}
			if (foundTarget)
				break;
		}
		int where = target;
		int prev;
		int pathCap = 1 << 30;
		while (path[where] > -1) {
			prev = path[where];
			pathCap = Math.min(pathCap, adjMatric[prev][where]);
			where = prev;
		}

		where = target;

		if (pathCap == 1 << 30)
			return 0;

		while (path[where] > -1) {
			prev = path[where];
			adjMatric[prev][where] -= pathCap;
			adjMatric[where][prev] += pathCap;
			where = prev;
		}

		return pathCap;

	}

	public static void main(String[] args) throws Exception {
		BufferedReader br = null;
		int caseNum = 0;
		if (debug) {
			br = new BufferedReader(new FileReader("C:\\Dev4Workspace\\Test\\in.txt"));
		} else {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		try {
			while (true) {
				caseNum++;
				String[] sp = br.readLine().split(" ");
				int from, to;
				nodeSize = Integer.parseInt(sp[0]);
				edgeSize = Integer.parseInt(sp[1]);

				if (nodeSize == 0 && edgeSize == 0) {
					break;
				}

				for (int i = 0; i < nodeSize + 2; i++) {
					Arrays.fill(adjMatric[i], 0);
					adjList[i] = new ArrayList<Integer>();
				}

				for (int i = 0; i < edgeSize; i++) {
					sp = br.readLine().split(" ");
					from = Integer.parseInt(sp[0]);
					to = Integer.parseInt(sp[1]);
					adjMatric[from][to]++;
					adjMatric[to][from]++;
					adjList[from].add(to);
					adjList[to].add(from);

				}
				sp = br.readLine().split(" ");
				from = Integer.parseInt(sp[0]);
				target = Integer.parseInt(sp[1]);
				adjMatric[source][from] = adjMatric[from][source] = 2;
				adjList[source].add(from);
				adjList[from].add(source);

				int res = max_flow();

				if (res == 2)
					System.out.println("Case " + caseNum + ": YES");
				else
					System.out.println("Case " + caseNum + ": NO");
			}
		} finally {
			try {
				if (br != null)
					br.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
}