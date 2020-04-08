#include <string>
#include <list>
#include <map>
#include <iostream>

bool sameLastLetters(std::string *s1, std::string *s2)
{
  if (s1->compare(*s2) == 0)
  { //Same string and we do not want a node to have a node to have an edge to itself
    return false;
  }

  const char *charSeq1 = s1->c_str();
  const char *charSeq2 = s2->c_str();
  int s1int[5];
  int s2int[5];

  for (int i = 0; i < 5; i++)
  {
    s1int[i] = charSeq1[i];
    s2int[i] = charSeq2[i];
  }

  for (int i = 0; i < 5; i++)
  {
    for (int j = 1; j < 5; j++)
    {
      if (s1int[j] == s2int[i])
      {
        s1int[j] = 0;
        s2int[i] = 1;
      }
    }
  }
  for (int i = 1; i < 5; i++)
  {
    if (s1int[i] != 0)
    {
      return false;
    }
  }

  return true;
}

int BFS(std::list<int> **graph, int start, int end, int nodeCount)
{
  if (start == end)
  {
    return 0;
  }

  std::list<int> layerList; //List of nodes we have to explore
  layerList.push_back(start);

  int visitedTracker[nodeCount]; //Array to keep track of visited nodes; not visited = 0, visited = 1
  for (int i = 0; i < nodeCount; i++)
  {
    visitedTracker[i] = 0;
  }
  visitedTracker[start] = 1;

  int predTracker[nodeCount]; // Store the predecessors of each node

  while (layerList.size() > 0)
  {
    int previousNode = layerList.front();
    layerList.pop_front();

    for (std::list<int>::iterator it = graph[previousNode]->begin(); it != graph[previousNode]->end(); it++)
    {
      int currentNode = *it;
      if (visitedTracker[currentNode] == 0)
      {
        visitedTracker[currentNode] = 1;
        layerList.push_back(currentNode);
        predTracker[currentNode] = previousNode;
        if (currentNode == end)
        {
          int pathLength = 0;
          while (currentNode != start)
          {
            pathLength++;
            currentNode = predTracker[currentNode];
          }
          return pathLength;
        }
      }
    }
  }
  return -1;
}

int main()
{
  int words;
  int queries;
  std::cin >> words;
  std::cin >> queries;

  std::map<std::string, int> lookupTable; //we store the words as unique integers instead of strings.

  std::list<int> *graph[words]; //the graph

  {
    std::map<int, std::string> reverseLookupTable;
    int i = -1;
    for (std::string line; i < words; i++)
    {
      std::getline(std::cin, line);
      //std::cout << "i is " << i << std::endl;
      if (!line.empty())
      {
        lookupTable[line] = i;
        reverseLookupTable[i] = line;
        graph[i] = new std::list<int>;
      }
    }
    for (i = 0; i < words; i++)
    {
      for (int j = 0; j < words; j++)
      {
        std::string word1 = reverseLookupTable[i];
        std::string word2 = reverseLookupTable[j];
        if (sameLastLetters(&word1, &word2))
        {
          graph[i]->push_back(j);
        }
      }
    }
  }

  int pathTotest[queries][2];

  for (int i = 0; i < queries; i++)
  {
    std::string inputString;
    std::cin >> inputString;
    int inIntegerForm = lookupTable[inputString];
    pathTotest[i][0] = inIntegerForm;

    std::cin >> inputString;
    inIntegerForm = lookupTable[inputString];
    pathTotest[i][1] = inIntegerForm;
  }
  for (int i = 0; i < queries; i++)
  {
    int src = pathTotest[i][0];
    int dest = pathTotest[i][1];
    int res = BFS(graph, src, dest, words);

    if (res == -1)
    {
      std::cout << "Impossible";
    }
    else
    {
      std::cout << res;
    }
    std::cout << std::endl;
  }
}