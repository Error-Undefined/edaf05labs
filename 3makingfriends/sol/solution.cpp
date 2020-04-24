#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>

typedef std::pair<int, int> intPair;

typedef std::pair<int, std::pair<int, int> *> edge;

auto edgeComp = [](edge *e1, edge *e2) { return e1->first > e2->first; };

int find(int v, int *parents)
{
  int p = v;

  while (parents[p] != -1)
  {
    p = parents[p];
  }

  while (parents[v] != -1)
  {
    int w = parents[v];
    parents[v] = p;
    v = w;
  }

  return p;
}

void unionSet(int u, int v, int *parents, int *sizes)
{
  u = find(u, parents);
  v = find(v, parents);

  if (sizes[u] < sizes[v])
  {
    parents[u] = v;
    sizes[v] += sizes[u];
  }
  else
  {
    parents[v] = u;
    sizes[u] += sizes[v];
  }
}

std::vector<edge *> *
kruskal(std::priority_queue<edge *, std::vector<edge *>, decltype(edgeComp)> *edges, int vertexCount)
{
  std::vector<edge *> *mst = new std::vector<edge *>; //vector to store edges of th emst
  int parents[vertexCount + 1];                       //Keep track of parents for union-find
  int sizes[vertexCount + 1];

  for (int i = 1; i <= vertexCount; i++)
  {
    parents[i] = -1;
    sizes[i] = 1;
  }

  while (edges->size() > 0)
  {
    edge *shortest = edges->top();
    edges->pop();

    int u = shortest->second->first;
    int v = shortest->second->second;

    int uF = find(u, parents);
    int vF = find(v, parents);

    if (uF != vF)
    {
      mst->push_back(shortest);
      unionSet(uF, vF, parents, sizes);
    }
  }

  return mst;
}

int main()
{

  int people, pairs;

  std::cin >> people;
  std::cin >> pairs;

  std::priority_queue<edge *, std::vector<edge *>, decltype(edgeComp)> edgeVector(edgeComp);
  std::vector<edge *> *mst;

  for (int M = 0; M < pairs; M++)
  {
    int person1, person2, weight;

    std::cin >> person1;
    std::cin >> person2;
    std::cin >> weight;

    intPair *nodePair = new intPair(person1, person2);

    edge *e = new edge(weight, nodePair);
    edgeVector.push(e);
  }

  mst = kruskal(&edgeVector, people);
  int mstLength = 0;

  for (std::vector<edge *>::iterator it = mst->begin(); it != mst->end(); it++)
  {
    mstLength += (*it)->first;
  }

  std::cout << mstLength << std::endl;

  while (false)
  {
    edge *e = edgeVector.top();
    edgeVector.pop();
    std::cout << "Edge: " << e->second->first << " - " << e->second->second << ", weight " << e->first << std::endl;
  }
}