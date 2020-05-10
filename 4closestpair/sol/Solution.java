package sol;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Solution {
  double distance(Point p1, Point p2) {
    return Math.hypot(p2.x - p1.x, p2.y - p1.y);
  }

  double bruteForce(Point[] xArray, int points) {
    if (points == 2) {
      return distance(xArray[0], xArray[1]);
    }

    double minDistance = Double.MAX_VALUE;
    for (int i = 0; i < points; i++) {
      for (int j = i + 1; j < points; j++) {
        double tempDistance = distance(xArray[i], xArray[j]);
        minDistance = Math.min(tempDistance, minDistance);
      }
    }
    return minDistance;
  }

  double closestRecursive(Point[] xArray, Point[] yArray, int xStart, int xEnd) {
    int points = xEnd - xStart;

    if (points < 4) {
      return bruteForce(xArray, points);
    }

    int midIndex = xStart + (points + 1) / 2;
    Point midPoint = xArray[midIndex];

    Point[] yLeft = new Point[midIndex - xStart];
    Point[] yRight = new Point[xEnd - midIndex];

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

    System.out.println(leftIndex + ", " + yLeft.length);
    System.out.println(rightIndex + ", " + yRight.length);
    System.out.println(points);

    double dL = closestRecursive(xArray, yLeft, xStart, midIndex);
    double dR = closestRecursive(xArray, yRight, midIndex, xEnd);

    double delta = Math.min(dL, dR);

    List<Point> lineSet = new ArrayList<>();
    for (Point p : xArray) {
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

    double result = closestRecursive(xArray, yArray, 0, points);

    System.out.println(result);
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