package backup;
import java.util.Arrays;
import java.util.Collections;

/**
 * find the biggest circle
 */
public class Solution2_FindBiggestCircle {
	private int[] graph;
	private int[] visited;
	private int[] globalVisited;
	private int max, counter;

	private void dfs(int curr) {
		if (visited[curr] == 1) {
			return;
		}
		globalVisited[curr] = visited[curr] = 1;
		counter++;
		if (max < counter) {
			max = counter;
		}
		dfs(graph[curr]);
	}

	public int solution(int[] A) {
		max = 0;
		graph = A;
		globalVisited = new int[A.length];
		for (int i = 0; i < A.length; i++) {
			if (globalVisited[i] == 1) {
				continue;
			}
			visited = new int[A.length];
			counter = 0;
			dfs(A[i]);
		}

		return max;
	}

	public static void main(String[] args) {
		Solution2_FindBiggestCircle solution = new Solution2_FindBiggestCircle();
		int[] a = { 5, 4, 0, 3, 1, 6, 2 };
		System.out.println(solution.solution(a));
	}
}
