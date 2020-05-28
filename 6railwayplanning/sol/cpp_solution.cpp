#include <iostream>
#include <list>
#include <vector>
#include <queue>

#define ever (;;)

/*
A graph edge (directed). It holds information about its origin, destination, current capacity,
original capacity, current flow, if it is deleted and the corresponding edge in the other direction.
*/
struct edge
{
  int source;
  int sink;
  int capacity;
  int originalCapacity;
  int flow = 0;
  bool deleted = false;
  edge *reverse;
};

/*
When we have run our network flow algorithm, we need to reset the capacities,
flows and deletion states of the edges
*/
void restoreGraph(std::vector<edge *> **graph, int nodes)
{
  for (int i = 0; i < nodes; i++)
  {
    for (edge *e : *graph[i])
    {
      e->capacity = e->originalCapacity;
      e->flow = 0;
      e->deleted = false;
    }
  }
}

/*
Utility function to return the minimum of two integers
*/
int min(int i1, int i2)
{
  return (i1 < i2) ? i1 : i2;
}

/*
Executes breadth first search on the graph from source to sink. Stores 
the edge path in the parent vector
*/
int bfs(std::vector<edge *> **residualGraph, int source, int sink, int nodes, edge **parent)
{

  // Queue for nodes to check in BFS
  std::list<int> nodeQueue;

  // Keep track of visited nodes
  int visitedTracker[nodes];
  std::fill(visitedTracker, visitedTracker + nodes, -1);
  visitedTracker[source] = 1;

  nodeQueue.push_back(source);

  while (!nodeQueue.empty())
  {
    int current = nodeQueue.front();
    nodeQueue.pop_front();

    // Iterate over all outgoing edges from a node
    for (edge *nextEdge : *residualGraph[current])
    {
      int nextNode = nextEdge->sink;

      // We have 3 conditions for us to want an edge in our path:
      // - it is not visited
      // - it has not been deleted
      // - its capacity is greater than 0 and it can hold some flow
      if (visitedTracker[nextNode] == -1 && !nextEdge->deleted && nextEdge->capacity > 0)
      {
        parent[nextNode] = nextEdge;
        visitedTracker[nextNode] = 1;
        nodeQueue.push_back(nextNode);

        // We have reached the end and thus found a path
        if (nextNode == sink)
        {
          return 1;
        }
      }
    }
  }
  // No path was found
  return 0;
}

/*
 *Main algorithm for the network flow.
 */
int edmondsKarp(std::vector<edge *> **graph, int source, int sink, int nodes)
{
  // Initialize path vector
  edge *parent[nodes];

  // While BFS finds a path we can add flow
  while (bfs(graph, source, sink, nodes, parent) == 1)
  {
    // The flow we can add is the minimal capacity in the path found
    int pathDelta = INT32_MAX;
    for (int v = sink; v != source; v = parent[v]->source)
    {
      pathDelta = min(pathDelta, parent[v]->capacity);
    }

    // With the minimal flow found, we can update the flows
    for (int v = sink; v != source; v = parent[v]->source)
    {
      // The edge flow is increased by the path flow,
      // and decreased by that in the opposite direction
      edge *e = parent[v];
      e->flow += pathDelta;
      e->reverse->flow -= pathDelta;

      // The capacity is decreased by the flow, and set
      // to the flow in the reverse direction
      e->capacity = e->originalCapacity - e->flow;
      e->reverse->capacity = e->flow;
    }
  }

  // The maximum flow is given for example by the sum of the flows out from the source
  int flow = 0;
  for (edge *e : *graph[0])
  {
    flow += e->flow;
  }

  return flow;
}

int main()
{
  // Main graph variables
  int N, M, C, P;
  std::cin >> N;
  std::cin >> M;
  std::cin >> C;
  std::cin >> P;

  //Store the edges in an array so we easily can remove an edge later
  edge *edges[M][2];

  //Initialize the graph with adjacency lists
  std::vector<edge *> *graph[N];
  for (int i = 0; i < N; i++)
  {
    graph[i] = new std::vector<edge *>;
  }

  // Edge creation. Because the graph is undirected, we interpret this in
  // the ford-fuelkerson algorithm as if every edge already has a backwards edge
  for (int i = 0; i < M; i++)
  {
    int u, v, cap;
    std::cin >> u;
    std::cin >> v;
    std::cin >> cap;

    edge *e1 = new edge;
    edge *e2 = new edge;

    //Create edges and reverse edges
    e1->source = u;
    e1->sink = v;
    e1->capacity = cap;
    e1->originalCapacity = cap;

    e2->source = v;
    e2->sink = u;
    e2->capacity = cap;
    e2->originalCapacity = cap;

    // These edges are coupled
    e1->reverse = e2;
    e2->reverse = e1;

    // Added to the graph
    graph[e1->source]->push_back(e1);
    graph[e2->source]->push_back(e2);

    // And added to the edge vector for easy removal later
    edges[i][0] = e1;
    edges[i][1] = e2;
  }

  int removals[P];
  for (int i = 0; i < P; i++)
  {
    std::cin >> removals[i];
  }

  // We use a binary search to find the number of deletions.
  // This reduces overall complexity to O(Cm^2logm) as restoring the graph is O(m), the search is
  // O(log m), the Edmonds-karp algorithm is O(Cm) and IO is O(m + n). This gives a complexity of
  // O(m * log m * Cm + m + n) = O(Cm^2logm)

  //Upper bound, lower bound and number of deletions in the binary search
  int upper = P;
  int lower = 0;
  int i;

  // Variables to hold different flows
  int maxFlow = INT32_MAX;
  int newFlow = maxFlow;
  int trueFlow;

  for
    ever
    {
      i = (upper + lower) / 2;
      newFlow = maxFlow;

      //  Restore the graph
      restoreGraph(graph, N);
      // Delete the i nodes as given
      for (int j = 0; j < i; j++)
      {
        edges[removals[j]][0]->deleted = true;
        edges[removals[j]][1]->deleted = true;
      }

      //Execute the algorithm
      maxFlow = edmondsKarp(graph, 0, N - 1, N);

      if (maxFlow >= C)
      {
        //More deletions are needed. Test deleting one more and see if this is the answer
        restoreGraph(graph, N);
        for (int j = 0; j < i + 1; j++)
        {
          edges[removals[j]][0]->deleted = true;
          edges[removals[j]][1]->deleted = true;
        }

        newFlow = maxFlow;
        maxFlow = edmondsKarp(graph, 0, N - 1, N);

        //We were on the answer, we can break out and finish
        if (maxFlow < C && newFlow >= C)
        {
          trueFlow = newFlow;
          break;
        }
        // Raise the lower bound to do more deletions
        lower = i;
      }
      else
      {
        //Less deletions are needed. Test deleting one less and see if that is the answer
        for (int j = 0; j < i - 1; j++)
        {
          edges[removals[j]][0]->deleted = true;
          edges[removals[j]][1]->deleted = true;
        }
        newFlow = maxFlow;
        maxFlow = edmondsKarp(graph, 0, N - 1, N);
        if (maxFlow >= C && newFlow < C)
        {
          trueFlow = maxFlow;
          break;
        }
        //Lower the upper bound to do less deletions
        upper = i;
      }

      //std::cout << "i (deletions): " << i << " trueflow: " << newFlow << "\n";
    }

  //std::cout << "Answer: max flow is " << trueFlow << " after " << i << " deletions\n";

  std::cout << i << " " << trueFlow << std::endl;
}
