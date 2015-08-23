import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 658
 */

class Release {
	int bug, time;

	public boolean isOK(Patch patch) {
		if ((patch.expect & this.bug) != patch.expect) {
			return false;
		}
		if ((patch.unexpect & this.bug) != 0) {
			return false;
		}
		return true;
	}

	public Release apply(Patch patch) {
		Release r = new Release();
		r.bug = this.bug & patch.fix;
		r.bug = r.bug | patch.introduce;
		r.time = this.time + patch.second;
		return r;
	}

	public String toString() {
		return "Release : [bug " + Integer.toBinaryString(bug) + " age " + time + "]";
	}
}

class Patch {
	int expect, unexpect, fix, introduce, second;

	public void initExpect(String expectStr) {
		for (int j = 0; j < expectStr.length(); j++) {
			char c = expectStr.charAt(j);
			switch (c) {
			case '+':
				this.expect = this.expect | (1 << j);
				break;
			case '-':
				this.unexpect = this.unexpect | (1 << j);
				break;
			}
		}
	}

	public void initFix(String fixStr) {
		for (int j = 0; j < fixStr.length(); j++) {
			char c = fixStr.charAt(j);
			switch (c) {
			case '+':
				this.introduce = this.introduce | (1 << j);
				break;
			case '-':
				this.fix = this.fix | (1 << j);
				break;
			}
		}
		this.fix = (~this.fix);
	}

	public String toString() {
		return "Patch : [expect " + Integer.toBinaryString(expect) + " unexpect " + Integer.toBinaryString(unexpect) + " fix " + Integer.toBinaryString(fix) + " introduce "
				+ Integer.toBinaryString(introduce) + " second " + second + "]";
	}
}

public class Main {
	static boolean debug = false;

	private static Integer bfs(Release release, ArrayList<Patch> allPatch) {
		LinkedList<Release> queue = new LinkedList<Release>();
		HashMap<Integer, Integer> allRelease = new HashMap<Integer, Integer>();
		queue.add(release);
		while (!queue.isEmpty()) {
			Release r = queue.getFirst();
			queue.removeFirst();
			if (Main.debug) {
				System.out.println(r);
			}

			Integer oldTime = allRelease.get(r.bug);
			if (oldTime == null || r.time < oldTime) {
				allRelease.put(r.bug, r.time);
				if (r.bug != 0) {
					for (Patch patch : allPatch) {
						if (r.isOK(patch)) {
							queue.addLast(r.apply(patch));
						}
					}
				}
			}
		}
		return allRelease.get(0);
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int n, m;
		for (int index = 1;; index++) {
			StringTokenizer st = new StringTokenizer(cin.nextLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			if (n == 0 && m == 0)
				break;
			ArrayList<Patch> allPatch = new ArrayList<Patch>();
			Release release = new Release();
			for (int j = 0; j < n; j++) {
				release.bug = release.bug | (1 << j);
			}

			for (int i = 0; i < m; i++) {
				Patch patch = new Patch();
				st = new StringTokenizer(cin.nextLine());
				patch.second = Integer.parseInt(st.nextToken());
				patch.initExpect(st.nextToken());
				patch.initFix(st.nextToken());
				allPatch.add(patch);
			}
			System.out.println("Product " + index);
			Integer time = bfs(release, allPatch);
			if (time == null) {
				System.out.println("Bugs cannot be fixed.\n");
			} else {
				System.out.println("Fastest sequence takes " + time + " seconds.\n");
			}
		}
	}
}