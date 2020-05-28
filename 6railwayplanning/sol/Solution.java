package sol;

import java.util.ArrayList;

import java.util.List;

import java.util.Scanner;

public class Solution {

  List<List<Edge>> graph;
  List<List<Edge>> capacity;

  int bfs(int source, int sink) {
    return 0;
  }

  int maximumFlow(List<List<Edge>> graph, int source, int sink) {
    int flow = 0;

    return flow;
  }

  void run() {
    Scanner scan = new Scanner(System.in);
    int N = scan.nextInt();
    int M = scan.nextInt();
    // int C = scan.nextInt();
    int P = scan.nextInt();

    Edge[][] edgeVector = new Edge[M][2];

    for (int i = 0; i < M; i++) {
      int u = scan.nextInt();
      int v = scan.nextInt();
      int capacity = scan.nextInt();

      Edge e1 = new Edge(v, capacity, 0);
      Edge e2 = new Edge(u, capacity, 0);

      edgeVector[i][0] = e1;
      edgeVector[i][1] = e2;
    }

    List<List<Edge>> graph = new ArrayList<>(N);
    for (int i = 0; i < N; i++) {
      graph.add(i, new ArrayList<Edge>());
    }

    for (int i = 0; i < M; i++) {
      Edge toAdd1 = edgeVector[i][0];
      Edge toAdd2 = edgeVector[i][1];
      graph.get(toAdd2.dest).add(toAdd1);
      graph.get(toAdd1.dest).add(toAdd2);
    }

    int[] removals = new int[P];
    for (int i = 0; i < P; i++) {
      removals[i] = scan.nextInt();
    }
    scan.close();

    // edgeVector[removals[0]][0].deleted = true;
    // edgeVector[removals[0]][1].deleted = true;

    // edgeVector[removals[1]][0].deleted = true;
    // edgeVector[removals[1]][1].deleted = true;

    int currentFlow = 0;
    // int oldFlow = currentFlow;
    int finalIndex = 0;

    // System.out.println(currentFlow);

    for (int i = 0; i < 15; i++) {
      edgeVector[removals[i]][0].deleted = true;
      edgeVector[removals[i]][1].deleted = true;
      // oldFlow = currentFlow;
      finalIndex = i + 1;
    }
    currentFlow = maximumFlow(graph, 0, N - 1);
    System.out.println(finalIndex + " " + currentFlow);

  }

  public static void main(String[] args) {
    Solution sol = new Solution();
    sol.run();
  }

  class Edge {
    int dest, capacity, flow;
    boolean deleted;

    Edge(int dest, int capacity, int flow) {
      this.dest = dest;
      this.capacity = capacity;
      this.flow = flow;
      deleted = false;
    }
  }
}