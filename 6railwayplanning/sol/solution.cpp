#include <iostream>
#include <list>
#include <vector>

struct edge
{
  int u;
  int v;
  int c;
  bool deleted;
};

int maximumFlow(int start, int end, int edges, int nodes, std::vector<edge *> **graph)
{
  //Initialize flow
  int edgeFlow[edges];
  for (int i = 0; i < edges; i++)
  {
    edgeFlow[i] = 0;
  };
  std::vector<edge *> *residualGraph[nodes];
  for (int i = 0; i < nodes; i++)
  {
    residualGraph[i] = new std::vector<edge *>;
  }
}

int main()
{
  int N, M, C, P;
  std::cin >> N;
  std::cin >> M;
  std::cin >> C;
  std::cin >> P;

  //Store the edges in an array so we easily can remove an edge later
  edge *edges[M];

  //Initialize the graph with adjacency lists
  std::vector<edge *> *graph[N];
  for (int i = 0; i < N; i++)
  {
    graph[i] = new std::vector<edge *>;
  }

  for (int i = 0; i < M; i++)
  {
    edge *e = new edge;
    std::cin >> e->u;
    std::cin >> e->v;
    std::cin >> e->c;
    e->deleted = false;
    edges[i] = e;
    graph[e->u]->push_back(e);
    graph[e->v]->push_back(e);
  }

  int removals[P];
  for (int i = 0; i < P; i++)
  {
    std::cin >> removals[i];
  }

  for (int i = 0; i < N; i++)
  {
    std::vector<edge *> *adjList = graph[i];
    std::cout << "Node " << i << " has edges:\n";
    for (std::vector<edge *>::iterator it = adjList->begin(); it != adjList->end(); it++)
    {
      if (!(*it)->deleted)
      {
        std::cout << (*it)->u << "-" << (*it)->v << " with cost: " << (*it)->c << "\n";
      }
    }
  }
}