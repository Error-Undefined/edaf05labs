package sol;

import java.util.Scanner;

public class Solution {

  void run() {
    Scanner scan = new Scanner(System.in);
    int N = scan.nextInt();
    int M = scan.nextInt();
    int C = scan.nextInt();
    int P = scan.nextInt();

    Edge[] edges = new Edge[M];
    for (int i = 0; i < M; i++) {
      Edge e = new Edge(scan.nextInt(), scan.nextInt(), scan.nextInt());
      edges[i] = e;
    }

    int[] removals = new int[P];
    for (int i = 0; i < P; i++) {
      removals[i] = scan.nextInt();
    }
    scan.close();
    for (Edge e : edges) {
      System.out.println("Edge: " + e.u + "-" + e.v + ", cost " + e.c);
    }
    for (int i : removals) {
      System.out.println("Remove: " + i);
    }
  }

  public static void main(String[] args) {
    Solution sol = new Solution();
    sol.run();
  }

  class Edge {
    int u, v, c;
    boolean deleted;

    Edge(int u, int v, int c) {
      this.u = u;
      this.v = v;
      this.c = c;
      deleted = false;
    }
  }
}