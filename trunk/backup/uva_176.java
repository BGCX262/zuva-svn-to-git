import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

//A11 1612 1720
//A12 1508 1636
//S16 1152 1250
//S17 1048 1134
//S17 1272 1326
//#
//S16 1288 A11 1543
//S18 1202 S18 1102
//S18 1202 S18 1101
//S18 1202 S18 1206
//S18 1202 S18 1203
//S17 0902 S17 1044
//S17 0906 S17 0902
//S17 0902 S17 0906
//S17 0905 S17 0903
//S17 0903 S17 0905
//S17 0903 S17 0907
//S16 1100 S16 1000
//S16 1101 S16 1000
//#
//213
//49
//151
//197
//202
//176
//1
//197
//198
//0
//1
//49
//#
//
//A11 1098 1098
//S11 1098 1098
//S11 1100 1100
//S06 1988 2026
//S06 2180 2238
//S06 2362 2396
//#
//S16 1288 S16 1288
//S06 2301 S06 2101
//A11 1102 A11 1103
//#
//0
//261
//2


public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		SPFAGraph graph = new SPFAGraph();
		graph.initInter();
		boolean missing = true;
		List<SourceDest> allST = new ArrayList<SourceDest>();
		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			if (line.equals("#")) {
				if (!missing) {
					break;
				} else {
					missing = false;
					continue;
				}
			}
			StringTokenizer st = new StringTokenizer(line);
			if (missing) {
				String road = st.nextToken();
				String from = st.nextToken();
				String to = st.nextToken();
				SPFAGraph.missingRoads.add(new MissingRoad(road, from, to));
			} else {
				String fromRoad = st.nextToken();
				String from = st.nextToken();
				String toRoad = st.nextToken();
				String to = st.nextToken();
				SourceDest sd = new SourceDest(fromRoad, from, toRoad, to);
				allST.add(sd);
			}
		}
		graph.initMissingRoad();
		for (SourceDest st : allST) {
			System.out.println(graph.calDistance(st));
		}
	}
}

class Intersection {
	int street, avenue, index;
	Set<Intersection> connect = new HashSet<Intersection>();

	public Intersection(int s, int a) {
		this.street = s;
		this.avenue = a;
		this.index = this.street * SPFAGraph.size + this.avenue;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj instanceof Intersection) {
			return ((Intersection) obj).street == this.street && ((Intersection) obj).avenue == this.avenue;
		}
		return false;
	}

	@Override
	public String toString() {
		String s = "st:" + this.street + ", ave:" + this.avenue + ", cons:";
		s += " " + this.connect.size() + " ";
		for (int i = 0; i < this.connect.size(); i++) {
			s += "[st:" + ((Intersection) this.connect.toArray()[i]).street + ", ave:" + ((Intersection) this.connect.toArray()[i]).avenue + "]";
		}
		return s;
	}
}

class SPFAGraph {
	public static int size = 50;
	public static int maxDist = size * size * size;
	public static List<Intersection> allInt = new ArrayList<Intersection>();
	public static List<MissingRoad> missingRoads = new ArrayList<MissingRoad>();
	public static int[][] distance = new int[size * size][size * size];

	public void spfa(Intersection source) {
		initDistance();
		LinkedList<Intersection> queue = new LinkedList<Intersection>();
		boolean isInQueue[] = new boolean[size * size];
		queue.addLast(allInt.get(source.index));
		isInQueue[source.index] = true;
		while (queue.size() > 0) {
			Intersection curr = queue.getFirst();

			queue.removeFirst();
			isInQueue[curr.index] = false;
			for (Intersection aj : curr.connect) {
				if (distance[source.index][curr.index] + 1 < distance[source.index][aj.index]) {
					distance[source.index][aj.index] = distance[source.index][curr.index] + 1;
					// if (Main.debug) {
					// System.out.println("distance[" + source.index + "][" +
					// aj.index + "]:" + distance[source.index][aj.index]);
					// }
					if (!isInQueue[aj.index]) {
						if (queue.size() > 0 && distance[source.index][aj.index] < distance[source.index][queue.getFirst().index]) {
							queue.addFirst(aj);
						} else {
							queue.addLast(aj);
						}
						isInQueue[aj.index] = true;
					}
				}
			}
		}
	}

	private int getDistanceFromUTurnSource(SourceDest sd) {
		int dist = 0;
		for (MissingRoad mr : missingRoads) {
			if (sd.source.num % 2 == 0 && sd.source.isStreet == mr.to.isStreet && sd.source.inter.street == mr.to.inter.street
					&& sd.source.inter.avenue == mr.to.inter.avenue) {
				dist = ((sd.source.num - mr.to.num) / 2 - 1) + ((99 - (mr.to.num + 1)) / 2);
				break;
			} else if (sd.source.num % 2 == 1 && sd.source.isStreet == mr.from.isStreet && sd.source.inter.street == mr.from.inter.street
					&& sd.source.inter.avenue == mr.from.inter.avenue) {
				dist = ((mr.from.num + 1 - sd.source.num) / 2 - 1) + (mr.from.num / 2);
				break;
			}
		}
		return dist;
	}

	private int getDistanceFromUTurnDestination(SourceDest sd) {
		int dist = 0;
		for (MissingRoad mr : missingRoads) {
			if (sd.dest.num % 2 == 0 && sd.dest.isStreet == mr.from.isStreet && sd.dest.inter.street == mr.from.inter.street
					&& sd.dest.inter.avenue == mr.from.inter.avenue) {
				dist = mr.from.num / 2 + (mr.from.num - sd.dest.num) / 2 - 1;
				break;
			} else if (sd.dest.num % 2 == 1 && sd.dest.isStreet == mr.to.isStreet && sd.dest.inter.street == mr.to.inter.street
					&& sd.dest.inter.avenue == mr.to.inter.avenue) {
				dist = mr.to.num / 2 + (mr.to.num + 1 - sd.dest.num) / 2 - 1;
				break;
			}
		}
		return dist;
	}

	private int getUTurnDistanceFromInter(int street, int avenue) {
		int dist = 0;
		for (MissingRoad mr : missingRoads) {
			if (mr.from.isStreet && mr.from.inter.street == street) {
				if (mr.from.inter.avenue == avenue) {
					if (dist == 0 || dist > mr.from.num) {
						dist = mr.from.num;
					}
				} else if (mr.to.inter.avenue + 1 == avenue) {
					if (dist == 0 || dist > (98 - mr.to.num)) {
						dist = (98 - mr.to.num);
					}
				}
			} else if (!mr.from.isStreet && mr.from.inter.avenue == avenue) {
				if (mr.from.inter.street == street) {
					if (dist == 0 || dist > mr.from.num) {
						dist = mr.from.num;
					}
				} else if (mr.to.inter.street + 1 == street) {
					if (dist == 0 || dist > (98 - mr.to.num)) {
						dist = (98 - mr.to.num) / 2;
					}
				}
			}
		}
		return dist;
	}

	public int calDistance(SourceDest sd) {
		if (sd.source.inter.equals(sd.dest.inter) && sd.source.isStreet == sd.dest.isStreet) {
			if (sd.source.num == sd.dest.num) {
				return 0;
			}
			if (sd.source.num % 2 == sd.dest.num % 2 && sd.dest.num % 2 == 0 && sd.dest.num < sd.source.num) {
				return (sd.source.num - sd.dest.num) / 2 - 1;
			}

			if (sd.source.num % 2 == sd.dest.num % 2 && sd.dest.num % 2 == 1 && sd.source.num < sd.dest.num) {
				return (sd.dest.num - sd.source.num) / 2 - 1;
			}

			for (MissingRoad mr : missingRoads) {
				if (sd.source.num % 2 == 0 && sd.dest.num % 2 == 1 && sd.source.isStreet == mr.to.isStreet && sd.source.inter.street == mr.to.inter.street
						&& sd.source.inter.avenue == mr.to.inter.avenue) {
					return (sd.source.num - mr.to.num) / 2 - 1 + ((sd.dest.num - (mr.to.num + 1)) / 2 - 1);
				} else if (sd.source.num % 2 == 1 && sd.dest.num % 2 == 0 && sd.source.isStreet == mr.from.isStreet
						&& sd.source.inter.street == mr.from.inter.street && sd.source.inter.avenue == mr.from.inter.avenue) {
					return (mr.from.num + 1 - sd.source.num) / 2 - 1 + (sd.dest.num - mr.from.num) / 2 - 1;
				}
			}
		}

		if (Main.debug) {
			System.out.println("source:" + sd.source + ", dest:" + sd.dest);
		}

		int sStreet, sAvenue, dStreet, dAvenue;
		int distBeforeEnterInter = getDistanceFromUTurnSource(sd);
		if (distBeforeEnterInter != 0) {
			if (sd.source.isStreet && sd.source.num % 2 == 0) {
				sStreet = sd.source.inter.street;
				sAvenue = sd.source.inter.avenue + 1;
			} else if (!sd.source.isStreet && sd.source.num % 2 == 0) {
				sStreet = sd.source.inter.street + 1;
				sAvenue = sd.source.inter.avenue;
			} else {
				sStreet = sd.source.inter.street;
				sAvenue = sd.source.inter.avenue;
			}
		} else {
			if (sd.source.num % 2 == 0) {
				sStreet = sd.source.inter.street;
				sAvenue = sd.source.inter.avenue;
			} else if (sd.source.isStreet && sd.source.num % 2 == 1) {
				sStreet = sd.source.inter.street;
				sAvenue = sd.source.inter.avenue + 1;
			} else {
				sStreet = sd.source.inter.street + 1;
				sAvenue = sd.source.inter.avenue;
			}
		}
		if (distBeforeEnterInter == 0) {
			if (sd.source.num % 2 == 0) {
				distBeforeEnterInter = sd.source.num / 2;
			} else {
				distBeforeEnterInter = (99 - sd.source.num) / 2;
			}
		}

		if (Main.debug) {
			System.out.println("distBeforeEnterInter :" + distBeforeEnterInter);
		}

		int distAfterLeavingInter = getDistanceFromUTurnDestination(sd);
		if (distAfterLeavingInter != 0) {
			if (sd.dest.isStreet && sd.dest.num % 2 == 1) {
				dStreet = sd.dest.inter.street;
				dAvenue = sd.dest.inter.avenue + 1;
			} else if (!sd.dest.isStreet && sd.dest.num % 2 == 1) {
				dStreet = sd.dest.inter.street + 1;
				dAvenue = sd.dest.inter.avenue;
			} else {
				dStreet = sd.dest.inter.street;
				dAvenue = sd.dest.inter.avenue;
			}
		} else {
			if (sd.dest.isStreet && sd.dest.num % 2 == 0) {
				dStreet = sd.dest.inter.street;
				dAvenue = sd.dest.inter.avenue + 1;
			} else if (!sd.dest.isStreet && sd.dest.num % 2 == 0) {
				dStreet = sd.dest.inter.street + 1;
				dAvenue = sd.dest.inter.avenue;
			} else {
				dStreet = sd.dest.inter.street;
				dAvenue = sd.dest.inter.avenue;
			}
		}
		initConnect();
		initMissingRoad();
		int uTurnDistanceFromSourceInter = getUTurnDistanceFromInter(sStreet, sAvenue);
		if (uTurnDistanceFromSourceInter == 0) {
			if (sd.source.isStreet && sd.source.num % 2 == 0) {
				setDisconnect(sd.source.inter.street, sd.source.inter.avenue, sd.source.inter.street, sd.source.inter.avenue + 1);
			} else if (sd.source.isStreet && sd.source.num % 2 == 1) {
				setDisconnect(sd.source.inter.street, sd.source.inter.avenue, sd.source.inter.street, sd.source.inter.avenue - 1);
			} else if (!sd.source.isStreet && sd.source.num % 2 == 0) {
				setDisconnect(sd.source.inter.street, sd.source.inter.avenue, sd.source.inter.street + 1, sd.source.inter.avenue);
			} else if (!sd.source.isStreet && sd.source.num % 2 == 1) {
				setDisconnect(sd.source.inter.street, sd.source.inter.avenue, sd.source.inter.street - 1, sd.source.inter.avenue);
			}
			if (sd.dest.isStreet && sd.dest.num % 2 == 0) {
				setDisconnect(sd.dest.inter.street, sd.dest.inter.avenue, dStreet, dAvenue);
			} else if (sd.dest.isStreet && sd.dest.num % 2 == 1) {
				setDisconnect(sd.dest.inter.street, sd.dest.inter.avenue, sd.dest.inter.street, sd.dest.inter.avenue + 1);
			} else if (!sd.dest.isStreet && sd.dest.num % 2 == 0) {
				setDisconnect(sd.dest.inter.street, sd.dest.inter.avenue, dStreet, dAvenue);
			} else if (!sd.dest.isStreet && sd.dest.num % 2 == 1) {
				setDisconnect(sd.dest.inter.street, sd.dest.inter.avenue, sd.dest.inter.street + 1, sd.dest.inter.avenue);
			}
		}
		this.spfa(allInt.get(sStreet * size + sAvenue));
		if (uTurnDistanceFromSourceInter == 0 && sd.source.inter.equals(sd.dest.inter)) {
			setSource2SourceDistance(sStreet, sAvenue);
		}

		int distanceBetweenSourceDestInter = 50 * (distance[(sStreet * size + sAvenue)][(dStreet * size + dAvenue)]);

		if (Main.debug) {
			System.out.println("distance between intersection :" + distanceBetweenSourceDestInter);
		}
		// System.out.println("distance[" + (sStreet * size + sAvenue) + "][" +
		// (dStreet * size + dAvenue) + "]:"
		// + distance[(sStreet * size + sAvenue)][(dStreet * size + dAvenue)]);
		//
		// System.out.println("source[" + sStreet + "][" + sAvenue + "]:" +
		// "dest:" + dStreet + ", " + dAvenue + ", size:" + size);
		// }

		if (distAfterLeavingInter == 0) {
			if (sd.dest.num % 2 == 0) {
				distAfterLeavingInter = (98 - sd.dest.num) / 2;
			} else {
				distAfterLeavingInter = (sd.dest.num - 1) / 2;
			}
		}
		if (Main.debug) {
			System.out.println("distAfterLeavingInter :" + distAfterLeavingInter);
		}
		return distBeforeEnterInter + distanceBetweenSourceDestInter + uTurnDistanceFromSourceInter + distAfterLeavingInter;
	}

	private void setSource2SourceDistance(int sStreet, int sAvenue) {
		int dist = 4;
		distance[sStreet * size + sAvenue][sStreet * size + sAvenue] = dist;
	}

	public void initDistance() {
		int size2 = size * size;
		for (int i = 0; i < size2; i++) {
			for (int j = 0; j < size2; j++) {
				distance[i][j] = maxDist;
				if (i == j) {
					distance[i][j] = 0;
				}
			}
		}
	}

	public void initInter() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				allInt.add(new Intersection(i, j));
			}
		}
	}

	public void initConnect() {

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				setConnect(i - 1, j, i, j);
				setConnect(i + 1, j, i, j);
				setConnect(i, j + 1, i, j);
				setConnect(i, j - 1, i, j);
			}
		}
	}

	public void initMissingRoad() {
		for (MissingRoad road : missingRoads) {
			// if (Main.debug) {
			// System.out.println("Missing road from:" + road.from + ", to :" +
			// road.to);
			// }
			if (road.from.isStreet) {
				int block1 = road.from.inter.avenue;
				int block2 = road.to.inter.avenue + 1;
				for (int i = block1; i < block2; i++) {
					setDisconnect(road.from.inter.street, i, road.from.inter.street, i + 1);
				}
			} else {
				int block1 = road.from.inter.street;
				int block2 = road.to.inter.street + 1;
				for (int i = block1; i < block2; i++) {
					setDisconnect(i, road.from.inter.avenue, i + 1, road.from.inter.avenue);
				}
			}
		}
	}

	private void setConnect(int i, int j, int i2, int j2) {
		if (i < 0 || i >= size || j < 0 || j >= size || i2 < 0 || i2 >= size || j2 < 0 || j2 >= size)
			return;

		// if (Main.debug)
		// System.out.println("setConnect,i:" + i + ",j:" + j + ",i2:" + i2 +
		// ",j2:" + j2);
		int index1 = i * size + j;
		int index2 = i2 * size + j2;
		allInt.get(index1).connect.add(allInt.get(index2));
		allInt.get(index2).connect.add(allInt.get(index1));
	}

	private void setDisconnect(int i, int j, int i2, int j2) {
		// if (Main.debug)
		// System.out.println("setDisconnect,i:" + i + ",j:" + j + ",i2:" + i2 +
		// ",j2:" + j2);
		if (i < 0 || i >= size || j < 0 || j >= size || i2 < 0 || i2 >= size || j2 < 0 || j2 >= size)
			return;
		int index1 = i * size + j;
		int index2 = i2 * size + j2;
		allInt.get(index1).connect.remove(allInt.get(index2));
		allInt.get(index2).connect.remove(allInt.get(index1));
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < size * size; i++) {
			for (int j = 0; j < size * size; j++) {
				sb.append(distance[i][j] + " ");
			}
			sb.append("\n");
		}
		sb.append("missing:\n");
		for (MissingRoad r : missingRoads) {
			sb.append(r.toString() + "\n");
		}
		return sb.toString();
	}
}

class Address {
	boolean isStreet = false;
	Intersection inter;
	int num;

	Address(String road, String address) {
		if (road.charAt(0) == 'S') {
			isStreet = true;
		} else {
			isStreet = false;
		}
		int street, avenue;
		if (isStreet) {
			street = Integer.parseInt(road.substring(1));
			avenue = Integer.parseInt(address.substring(0, 2));
		} else {
			avenue = Integer.parseInt(road.substring(1));
			street = Integer.parseInt(address.substring(0, 2));
		}
		inter = SPFAGraph.allInt.get(street * SPFAGraph.size + avenue);
		this.num = Integer.parseInt(address.substring(2));
	}

	public String toString() {
		return inter + ", num:" + num + ", isStreet:" + isStreet;
	}
}

class SourceDest {
	Address source;
	Address dest;

	SourceDest(String fR, String f, String tR, String t) {
		this.source = new Address(fR, f);
		this.dest = new Address(tR, t);
	}
}

class MissingRoad {
	Address from;
	Address to;

	MissingRoad(String road, String from, String to) {
		this.from = new Address(road, from);
		this.to = new Address(road, to);
		if ((!this.from.isStreet && this.from.inter.street > this.to.inter.street) || (this.from.isStreet && this.from.inter.avenue > this.to.inter.avenue)) {
			Address t = this.from;
			this.from = this.to;
			this.to = t;
		}
	}

	public String toString() {
		return "from:" + from.toString() + ", to:" + to.toString();
	}
}
