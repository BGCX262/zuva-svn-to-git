import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * uva 657 - The die is cast
 */

class Pixel {
	enum Type {
		Back, Dot, Dice;
	};

	int visited = 0;
	List<Pixel> neighbor = new ArrayList<Pixel>();
	Type type;

	public String toString() {
		return " has neighbor " + this.neighbor.size() + ", visited " + visited + ", type:" + this.type;
	}
}

class Dice implements Comparable<Dice> {
	private List<Pixel> dots = new ArrayList<Pixel>();
	int num = 0;

	Dice(Pixel p) {
		if (Main.debug) {
			System.out.println("=========================================================");
		}

		dfsDice(p);
		for (Pixel d : dots) {
			if (d.visited == 1) {
				num++;
				dfsDot(d);
			}
		}
	}

	void dfsDice(Pixel p) {
		if (Main.debug) {
			System.out.println("dfsDice:" + p);
		}
		p.visited = 1;
		if (p.type == Pixel.Type.Dot) {
			dots.add(p);
		}
		for (Pixel n : p.neighbor) {
			if (n.visited == 0) {
				dfsDice(n);
			}
		}
	}

	void dfsDot(Pixel p) {
		p.visited = 2;
		for (Pixel n : p.neighbor) {
			if (n.visited == 1 && n.type == Pixel.Type.Dot) {
				dfsDot(n);
			}
		}
	}

	@Override
	public int compareTo(Dice o) {
		return this.num - o.num;
	}
}

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int throwIndex = 0;
		while (cin.hasNext()) {
			throwIndex++;
			String line = cin.nextLine();
			StringTokenizer st = new StringTokenizer(line);
			int col = Integer.parseInt(st.nextToken());
			int row = Integer.parseInt(st.nextToken());
			if (row == 0 && col == 0)
				break;
			List<Pixel> allNotBackgroud = new ArrayList<Pixel>();
			Pixel picture[][] = new Pixel[row][col];
			for (int i = 0; i < row; i++) {
				line = cin.nextLine();
				if (Main.debug)
					System.out.println("line:" + line);
				for (int j = 0; j < col; j++) {
					Pixel pixel = new Pixel();
					if (line.charAt(j) == '*') {
						pixel.type = Pixel.Type.Dice;
					} else if (line.charAt(j) == '.') {
						pixel.type = Pixel.Type.Back;
					} else if (line.charAt(j) == 'X') {
						pixel.type = Pixel.Type.Dot;
					}
					picture[i][j] = pixel;
					if (pixel.type == Pixel.Type.Back) {
						continue;
					}
					if (i - 1 >= 0 && picture[i - 1][j].type != Pixel.Type.Back) {
						picture[i - 1][j].neighbor.add(pixel);
						pixel.neighbor.add(picture[i - 1][j]);
					}
					if (j - 1 >= 0 && picture[i][j - 1].type != Pixel.Type.Back) {
						picture[i][j - 1].neighbor.add(pixel);
						pixel.neighbor.add(picture[i][j - 1]);
					}
					allNotBackgroud.add(pixel);
				}
			}
			List<Dice> dices = new ArrayList<Dice>();
			for (Pixel n : allNotBackgroud) {
				if (n.visited == 0) {
					dices.add(new Dice(n));
				}
			}
			Collections.sort(dices);
			System.out.println("Throw " + throwIndex);
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < dices.size(); i++) {
				if (i == 0)
					sb.append(dices.get(i).num);
				else {
					sb.append(" ");
					sb.append(dices.get(i).num);
				}
			}
			sb.append("\n");
			System.out.println(sb.toString());
		}
	}
}
