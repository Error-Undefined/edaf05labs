package sol;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Solution {
  /**
   * Finds the distance between two points. Returns 0 if the same point is passed
   * in twice.
   * 
   * @param p1 a point
   * @param p2 another point
   * @return the distance between these points.
   */
  double distance(Point p1, Point p2) {
    return Math.hypot(p2.x - p1.x, p2.y - p1.y);
  }

  /**
   * Brute forces a solution of the closest points.
   * 
   * @param xArray an array of points
   * @param points the number of points to check
   * @return the distance between the two closest points as a double
   */
  double bruteForce(Point[] pointArray, int points) {
    if (points == 2) {
      return distance(pointArray[0], pointArray[1]);
    }

    double minDistance = Double.MAX_VALUE;
    for (int i = 0; i < points; i++) {
      for (int j = i + 1; j < points; j++) {
        double tempDistance = distance(pointArray[i], pointArray[j]);
        minDistance = Math.min(tempDistance, minDistance);
      }
    }
    return minDistance;
  }

  // If we see the recursion as a tree, any layer of the tree has O(n) time
  // complexity
  //
  // there are log n layers, which gives a total time complexity of O(n*log n)
  double closestRecursive(Point[] xArray, Point[] yArray, int xStart, int xEnd) {
    int points = yArray.length;

    if (points < 4) {
      return bruteForce(yArray, points);
    }

    int midIndex = xStart + (points + 1) / 2;
    Point midPoint = xArray[midIndex];

    int yLeftLength = (points + 1) / 2;
    int yRightLength = points - yLeftLength;

    Point[] yLeft = new Point[yLeftLength];
    Point[] yRight = new Point[yRightLength];

    int leftIndex = 0;
    int rightIndex = 0;
    for (int i = 0; i < yArray.length; i++) {
      if (yArray[i].x <= midPoint.x && leftIndex < yLeft.length) {
        yLeft[leftIndex++] = yArray[i];
      } else if (rightIndex < yRight.length) {
        yRight[rightIndex++] = yArray[i];
      } else {
        yLeft[leftIndex++] = yArray[i];
      }
    }

    double dL = closestRecursive(xArray, yLeft, xStart, midIndex);
    double dR = closestRecursive(xArray, yRight, midIndex, xEnd);

    double delta = Math.min(dL, dR);

    List<Point> lineSet = new ArrayList<>();
    for (Point p : yArray) {
      if (Math.abs(p.x - midPoint.x) < delta) {
        lineSet.add(p);
      }
    }

    double minInSet = Double.MAX_VALUE;
    for (int i = 0; i < lineSet.size(); i++) {
      for (int j = i + 1; j < lineSet.size() && j < i + 15; j++) {
        double tempDistance = distance(lineSet.get(i), lineSet.get(j));
        minInSet = Math.min(tempDistance, minInSet);
      }
    }

    return Math.min(minInSet, delta);
  }

  void run() {
    Scanner inputScanner = new Scanner(System.in);
    int points = inputScanner.nextInt();

    Point[] xArray = new Point[points];
    Point[] yArray = new Point[points];

    long t1 = System.currentTimeMillis();
    for (int i = 0; i < points; i++) {
      int x = inputScanner.nextInt();
      int y = inputScanner.nextInt();

      Point p = new Point(x, y);
      xArray[i] = p;
      yArray[i] = p;
    }
    inputScanner.close();
    long t2 = System.currentTimeMillis();

    long tio = t2 - t1;

    // System.out.println("Time for io: " + tio + "ms");

    Arrays.sort(xArray, (p1, p2) -> p1.x - p2.x);
    Arrays.sort(yArray, (p1, p2) -> p1.y - p2.y);

    double result = closestRecursive(xArray, yArray, 0, points);

    System.out.printf("%.6f\n", result);

    long t3 = System.currentTimeMillis();
    long tp = t3 - t1;

    // System.out.println("Total time: " + tp + "ms");
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