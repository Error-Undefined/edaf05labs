#include <iostream>
#include <list>

struct edge
{
  int u;
  int v;
  int c;
};

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
  std::list<edge *> *graph[N];
  for (int i = 0; i < N; i++)
  {
    graph[i] = new std::list<edge *>;
  }

  for (int i = 0; i < M; i++)
  {
    edge *e = new edge;
    std::cin >> e->u;
    std::cin >> e->v;
    std::cin >> e->c;
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
    std::list<edge *> *adjList = graph[i];
    std::cout << "Node " << i << " has edges:\n";
    for (std::list<edge *>::iterator it = adjList->begin(); it != adjList->end(); it++)
    {
      std::cout << (*it)->u << "-" << (*it)->v << " with cost: " << (*it)->c << "\n";
    }
  }
}