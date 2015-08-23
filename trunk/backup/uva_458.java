import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;
	static DataInputStream in = new DataInputStream(System.in);
	static DataOutputStream output = new DataOutputStream(System.out);

	public static void main(String[] args) {

		if (args.length > 0)
			debug = true;
		int c;
		try {
			while ((c = in.read()) != -1) {
				if (c == 13 || c == 10) {
					output.write(c);
				} else {
					output.write(c - 7);
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
