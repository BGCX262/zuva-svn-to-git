import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

/**
 * 10226
 */

public class Main {
	static boolean debug = false;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		if (args.length > 0)
			debug = true;

		Map<String, Long> trees = new TreeMap<String, Long>();
		boolean first = true;
		Long total = 0L;
		br.readLine();
		br.readLine();
		String line = null;
		while ((line = br.readLine()) != null) {
			if (debug) {
				System.out.println("line:" + line);
			}
			if (line.equals("")) {
				if (first) {
					first = false;
					printResult(trees, total);
					trees.clear();
					total = 0L;
					continue;
				} else {
					System.out.println("");
					printResult(trees, total);
					trees.clear();
					total = 0L;
					continue;
				}
			} else {
				total++;
				Long hit = trees.get(line);
				if (hit == null) {
					trees.put(line, 1L);
				} else {
					trees.put(line, hit + 1);
				}
			}
		}
		System.out.println("");
		printResult(trees, total);
	}

	private static void printResult(Map<String, Long> trees, Long total) {
		for (Entry<String, Long> entry : trees.entrySet()) {
			Long value = entry.getValue();
			String key = entry.getKey();
			System.out.printf("%s %.4f\n", key, (value * 1.0 / total * 100));
		}
	}
}
