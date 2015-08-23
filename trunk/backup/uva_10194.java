import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 10194
 */

class Team implements Comparable<Team> {
	int id;
	String name, iName;
	ArrayList<Integer> goal = new ArrayList<Integer>(30);
	ArrayList<Integer> againstGoal = new ArrayList<Integer>(30);
	int win, allGoal, allAgainstGoal, points, game, goalDiff, losses, ties;

	public Team(int id, String name) {
		super();
		this.id = id;
		this.name = name;
		char[] iName = new char[name.length()];
		for (int i = 0; i < this.name.length(); i++) {
			char c = this.name.charAt(i);
			if (c >= 'A' && c <= 'Z') {
				iName[i] = Character.toLowerCase(c);
			} else {
				iName[i] = c;
			}
		}
		this.iName = new String(iName);
		for (int i = 0; i < 30; i++) {
			goal.add(0);
			againstGoal.add(0);
		}
	}

	public String toString() {
		if (Main.debug)
			return this.name + " iName " + this.iName + " " + this.points + "p, " + this.game + "g (" + this.win + "-" + this.ties + "-" + this.losses + "), " + this.goalDiff + "gd (" + this.allGoal
					+ "-" + this.allAgainstGoal + ")";
		return this.name + " " + this.points + "p, " + this.game + "g (" + this.win + "-" + this.ties + "-" + this.losses + "), " + this.goalDiff + "gd (" + this.allGoal + "-" + this.allAgainstGoal
				+ ")";
	}

	@Override
	public int compareTo(Team o) {
		if (this.points > o.points) {
			return -1;
		} else if (this.points < o.points) {
			return 1;
		} else {
			if (this.win > o.win) {
				return -1;
			} else if (this.win < o.win) {
				return 1;
			} else {
				if (this.goalDiff > o.goalDiff) {
					return -1;
				} else if (this.goalDiff < o.goalDiff) {
					return 1;
				} else {
					if (this.allGoal > o.allGoal) {
						return -1;
					} else if (this.allGoal < o.allGoal) {
						return 1;
					} else {
						if (this.game < o.game) {
							return -1;
						} else if (this.game > o.game) {
							return 1;
						} else {
							int size = this.iName.length() < o.iName.length() ? this.iName.length() : o.iName.length();
							for (int i = 0; i < size; i++) {
								if (this.iName.charAt(i) != o.iName.charAt(i)) {
									return this.iName.charAt(i) - o.iName.charAt(i);
								}
							}
							return this.iName.length() - o.iName.length();
						}
					}
				}
			}
		}
	}
}

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		int testN = Integer.parseInt(cin.nextLine());
		for (int test = 0; test < testN; test++) {
			String tournament = cin.nextLine();
			int teamN = Integer.parseInt(cin.nextLine());
			HashMap<String, Integer> teamMap = new HashMap<String, Integer>();
			ArrayList<Team> teams = new ArrayList<Team>(30);
			for (int i = 0; i < teamN; i++) {
				Team t = new Team(i, cin.nextLine());
				teamMap.put(t.name, t.id);
				teams.add(t);
			}

			int gameN = Integer.parseInt(cin.nextLine());
			for (int i = 0; i < gameN; i++) {
				StringTokenizer st = new StringTokenizer(cin.nextLine(), "#");
				Team t1 = teams.get(teamMap.get(st.nextToken()));
				StringTokenizer scoreSt = new StringTokenizer(st.nextToken(), "@");
				int g1 = Integer.parseInt(scoreSt.nextToken());
				int g2 = Integer.parseInt(scoreSt.nextToken());
				Team t2 = teams.get(teamMap.get(st.nextToken()));
				t1.goal.set(t2.id, g1);
				t1.againstGoal.set(t2.id, g2);
				t2.goal.set(t1.id, g2);
				t2.againstGoal.set(t1.id, g1);
				t1.allGoal += g1;
				t1.allAgainstGoal += g2;
				t2.allGoal += g2;
				t2.allAgainstGoal += g1;
				t1.game += 1;
				t2.game += 1;
				if (g1 > g2) {
					t1.win++;
					t2.losses++;
					t1.points += 3;
				} else if (g1 < g2) {
					t2.win++;
					t1.losses++;
					t2.points += 3;
				} else {
					t1.ties++;
					t2.ties++;
					t1.points += 1;
					t2.points += 1;
				}
				t1.goalDiff = t1.allGoal - t1.allAgainstGoal;
				t2.goalDiff = t2.allGoal - t2.allAgainstGoal;

			}
			if (Main.debug) {
				System.out.println("============================================================================");
				for (Team t : teams) {
					System.out.println(t);
				}
			}
			Collections.sort(teams);

			if (test != 0) {
				System.out.println("");
			}
			System.out.println(tournament);
			for (int i = 1; i <= teams.size(); i++) {
				System.out.println(i + ") " + teams.get(i - 1).toString());
			}
		}
	}
}
