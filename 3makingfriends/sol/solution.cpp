#include <iostream>
#include <vector>
#include <algorithm>

// Represents a pair of nodes.
typedef std::pair<int, int> intPair;

// Represents a weighted edge: first the weight, then the two nodes.
typedef std::pair<int, std::pair<int, int> *> edge;

// Comparator function for two edges.
bool edgeComp(edge *e1, edge *e2) { return e2->first < e1->first; };

/**
 * Find in union-find. Returns the set identifier (canonical member) of the set in which v is.
 */
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

/**
 * Union in union-find. Unites the sets of nodes u and v.
 */
void unionSet(int u, int v, int *parents, int *sizes)
{
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

/**
 * Kruskals algorithm for finding a minimum spanning tree. Returns a vector with all the edges in the mst.
 */
std::vector<edge *> *kruskal(std::vector<edge *> *edges, int vertexCount)
{
  std::vector<edge *> *mst = new std::vector<edge *>; //vector to store edges of the mst
  int parents[vertexCount + 1];                       //Keep track of parents for union-find
  int sizes[vertexCount + 1];                         //Size of the set that the current vertex is part of

  for (int i = 1; i <= vertexCount; i++)
  {
    parents[i] = -1; //Initialize all parents to -1 (null; no parent)
    sizes[i] = 1;    //Initialize all set sizes to 1
  }

  //Sort the edge vector: O(m log m); m <= n^2 ger O (m log n)
  std::sort(edges->begin(), edges->end(), edgeComp);

  //m loops; total O(m*alpha(n,m)) where alpha <= 4
  while (!edges->empty())
  {
    edge *shortest = edges->back();

    int u = shortest->second->first;
    int v = shortest->second->second;

    int uF = find(u, parents);
    int vF = find(v, parents);

    if (uF != vF)
    {
      mst->push_back(shortest);
      unionSet(uF, vF, parents, sizes);
    }
    edges->pop_back();
  }

  return mst;
}

int main()
{

  int people, pairs;

  std::cin >> people;
  std::cin >> pairs;

  std::vector<edge *> edgeVector;
  std::vector<edge *> *mst;

  for (int M = 0; M < pairs; M++)
  {
    int person1, person2, weight;

    std::cin >> person1;
    std::cin >> person2;
    std::cin >> weight;

    intPair *nodePair = new intPair(person1, person2);

    edge *e = new edge(weight, nodePair);
    edgeVector.push_back(e);
  }

  mst = kruskal(&edgeVector, people);
  int mstLength = 0;

  for (std::vector<edge *>::iterator it = mst->begin(); it != mst->end(); it++)
  {
    mstLength += (*it)->first;
  }

  std::cout << mstLength << std::endl;
}