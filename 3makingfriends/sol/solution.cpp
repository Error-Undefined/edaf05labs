#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>

typedef std::pair<int, int> intPair;

#define LARGER_THAN_MAX_INPUT 2000000

int *prim(std::list<intPair> **graph, int start, int people)
{
}

int main()
{

  int people, pairs;

  std::cin >> people;
  std::cin >> pairs;

  std::list<intPair *> *graph[people + 1];

  for (int N = 1; N <= people; N++)
  {
    graph[N] = new std::list<intPair *>;
  }

  for (int M = 0; M < pairs; M++)
  {
    int person1, person2, weight;

    std::cin >> person1;
    std::cin >> person2;
    std::cin >> weight;

    std::cout << person1 << ", " << person2 << ", " << weight << "\n";

    graph[person1]->push_back(new intPair(person2, weight));
    graph[person2]->push_back(new intPair(person1, weight));
  }

  std::cout << "no segfault\n";

  for (int i = 1; i <= people; i++)
  {
    std::list<intPair *> *edgeList = graph[i];
    std::cout << "Person " << i << "has edge to ";
    for (std::list<intPair *>::iterator it = edgeList->begin(); it != edgeList->end(); it++)
    {
      std::cout << (*it)->first << ", weight: " << (*it)->second << ";";
    }
    std::cout << std::endl;
  }
}