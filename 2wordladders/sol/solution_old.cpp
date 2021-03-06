#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>

bool sameLastLetters(std::string *s1, std::string *s2)
{
  if (s1 == s2 || s1->compare(*s2) == 0)
  { //Same reference or same string
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

//Breadth-first-search on the graph graph, with start start and end end. Returns path length, or -1 if no path was found.
int BFS(std::map<std::string, std::list<std::string> *> *graph, std::string *start, std::string *end)
{
  if (start->compare(*end) == 0)
  {
    return 0;
  }

  std::map<std::string, int> visitedMap;
  std::map<std::string, std::string> prevMap;

  std::list<std::string> layerList;
  layerList.push_back(*start);
  for (std::map<std::string, std::list<std::string> *>::iterator it = graph->begin(); it != graph->end(); ++it)
  {
    visitedMap[it->first] = 0;
  }

  visitedMap[*start] = 1;

  while (layerList.size() > 0)
  {
    std::string currentNode = layerList.front();
    layerList.pop_front();
    std::list<std::string> *adjacentList = graph->at(currentNode);
    for (std::list<std::string>::iterator it = adjacentList->begin(); it != adjacentList->end(); ++it)
    {
      if (visitedMap[*it] == 0)
      {
        visitedMap[*it] = 1;
        layerList.push_back(*it);
        prevMap[*it] = currentNode;
        if (end->compare(*it) == 0)
        {
          int retVal = 0;
          std::string endNodeIteration = *it;
          while (start->compare(endNodeIteration) != 0)
          {
            endNodeIteration = prevMap[endNodeIteration];
            ++retVal;
          }
          return retVal;
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
  scanf("%d", &words);
  scanf("%d", &queries);

  std::map<std::string, std::list<std::string> *> graph;

  {
    std::vector<std::string> inputWords;
    int i = 0;
    for (std::string line; i < words; i++)
    {
      std::getline(std::cin, line);
      if (!line.empty())
      {
        //std::cout << line << "\n";
        inputWords.push_back(line);
        graph[line] = new std::list<std::string>;
      }
      else
      {
        --i;
      }
    }

    for (i = 0; i < words; i++)
    {
      for (int j = 0; j < words; j++)
      {
        if (sameLastLetters(&inputWords[i], &inputWords[j]))
        {
          graph[inputWords[i]]->push_back(inputWords[j]);
        }
      }
    }
  }

  std::map<std::string *, std::string *> pathToTest;
  for (int i = 0; i < queries; ++i)
  {
    char part1[6];
    char part2[6];
    scanf("%s", part1);
    scanf("%s", part2);

    std::string *string1 = new std::string(part1);
    std::string *string2 = new std::string(part2);

    //std::cout << *string1 << " " << *string2 << "\n";
    pathToTest[string1] = string2;
  }

  /* for (std::map<std::string, std::list<std::string> *>::iterator it = graph.begin(); it != graph.end(); ++it)
  {
    std::cout << it->first << " has neighbours ";
    std::list<std::string> *list = it->second;
    for (std::list<std::string>::iterator it2 = list->begin(); it2 != list->end(); ++it2)
    {
      std::cout << *it2 << ",";
    }
    std::cout << "\n";
  } */

  for (std::map<std::string *, std::string *>::iterator it = pathToTest.begin(); it != pathToTest.end(); ++it)
  {
    int res = BFS(&graph, it->first, it->second);
    if (res >= 0)
    {
      std::cout << res;
    }
    else
    {
      std::cout << "Impossible";
    }
    std::cout << "\n";
  }
}