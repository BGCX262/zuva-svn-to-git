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
 * uva 10054 ,
 * 
 */

public class Main {
	static boolean debug = false;
	static int max;
	static List<Integer> source = new ArrayList<Integer>();
	static boolean[][] adjMatric = new boolean[26][26];
	static int[] time = new int[26];
	static boolean[] visited = new boolean[26];

	public static void main(String[] args) throws Exception {
		BufferedReader br = null;
		boolean first = true;
		if (debug) {
			br = new BufferedReader(new FileReader("C:\\Dev4Workspace\\Test\\in.txt"));
		} else {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		try {
			int caseNum = Integer.parseInt(br.readLine());

			for (;;) {
				String line = br.readLine();

				if (line == null) {
					for (Integer src : source) {
						Arrays.fill(visited, false);
					}

					System.out.println(max);
					break;
				}
				if (first && line.trim().length() < 1) {
					first = false;
					continue;
				}
				if (line.trim().length() < 1) {
					for (Integer src : source) {
						Arrays.fill(visited, false);
					}
					System.out.println(max + "\n");

					Arrays.fill(time, 0);
					Arrays.fill(visited, false);
					max = 0;
					for (int j = 0; j < 26; j++) {
						Arrays.fill(adjMatric[j], false);
					}
					source.clear();
					continue;
				}

				String[] sp = line.split(" ");
				time[sp[0].charAt(0) - 'A'] = Integer.parseInt(sp[1]);
				if (sp.length > 2) {
					for (Character c : sp[2].toCharArray()) {
						adjMatric[c - 'A'][sp[0].charAt(0) - 'A'] = true;
					}
				} else {
					source.add(sp[0].charAt(0) - 'A');
				}
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