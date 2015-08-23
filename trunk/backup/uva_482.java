import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 482
 */

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		int testN = Integer.parseInt(cin.nextLine());
		for (int test = 0; test < testN; test++) {
			cin.nextLine();
			ArrayList<Integer> allIndex = new ArrayList<Integer>();
			StringTokenizer st = new StringTokenizer(cin.nextLine());
			while (st.hasMoreTokens()) {
				allIndex.add(Integer.parseInt(st.nextToken()) - 1);
			}
			int n = allIndex.size();
			ArrayList<String> all = new ArrayList<String>(n);
			for (int i = 0; i < n; i++) {
				all.add(null);
			}
			st = new StringTokenizer(cin.nextLine());
			for (int i = 0; i < n; i++) {
				all.set(allIndex.get(i), st.nextToken());
			}
			
			if(test != 0){
				System.out.println("");	
			}
			
			for(String s:all){
				System.out.println(s);	
			}
		}
	}
}
