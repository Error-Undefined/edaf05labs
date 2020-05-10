package sol;

import java.util.Arrays;
import java.util.Scanner;

public class Solution {

  void run() {
    Scanner inputScanner = new Scanner(System.in);
    int points = inputScanner.nextInt();

    Point[] xArray = new Point[points];
    Point[] yArray = new Point[points];

    for (int i = 0; i < points; i++) {
      int x = inputScanner.nextInt();
      int y = inputScanner.nextInt();

      Point p = new Point(x, y);
      xArray[i] = p;
      yArray[i] = p;
    }
    inputScanner.close();

    Arrays.sort(xArray, (p1, p2) -> p1.x - p2.x);
    Arrays.sort(yArray, (p1, p2) -> p1.y - p2.y);

  }

  public static void main(String[] args) {
    Solution sol = new Solution();
    sol.run();
  }

  class Point {
    int x, y;

    Point(int x, int y) {
      this.x = x;
      this.y = y;
    }
  }
}