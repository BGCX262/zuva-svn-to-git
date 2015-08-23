package leetcode;
public class Solution_maxArea {
	public int maxArea(int[] height) {
		int max = 0;
		int i = 0, j = height.length - 1;
		while (i < j) {
			max = Math.max(max, (j - i) * Math.min(height[i], height[j]));
			if (height[i] < height[j]) {
				i++;
			} else {
				j--;
			}
		}
		return max;
	}

	public static void main(String[] args) {
		Solution_maxArea solution_maxArea = new Solution_maxArea();
		System.out.println(solution_maxArea.maxArea(null));
	}

}
