#include <iostream>
#include <unordered_map>
#include <map>
#include <stdio.h>
#include <list>
#include <chrono>
#include <ctime>

bool womanPrefers(int *prefList, int currentMan, int newMan)
{
  return prefList[newMan] < prefList[currentMan];
}

void GS(std::unordered_map<int, int *> *manMap, std::unordered_map<int, int *> *womanMap, std::unordered_map<int, int> *matchings)
{
  std::list<int> manList;                    // List of men to propose
  std::unordered_map<int, int> manProposals; // Map of indicies to keep track of proposals
  int couples = manMap->size();

  // Fill the list of men to propose and initialize the index map
  for (int i = 0; i < couples; ++i)
  {
    manList.push_back(i + 1);
    manProposals[i + 1] = 0;
  }

  while (manList.size() > 0)
  {
    int man = manList.front(); //The man to propose
    manList.pop_front();
    int *prefList = (*manMap)[man];
    int woman = prefList[manProposals[man]];
    manProposals[man]++; //increment the current man's index in the preference list

    if (matchings->count(woman) == 0)
    {
      (*matchings)[woman] = man;
    }
    else if (womanPrefers((*womanMap)[woman], (*matchings)[woman], man))
    {
      int oldMan = (*matchings)[woman];
      (*matchings)[woman] = man;
      manList.push_back(oldMan);
    }
    else
    {
      manList.push_back(man);
    }
  }
}

int main() // Main only handles IO.
{
  auto start = std::chrono::system_clock::now();

  std::unordered_map<int, int *> manMap;
  std::unordered_map<int, int *> womanMap;
  std::unordered_map<int, int> matchings;

  // scan data
  int lines;
  scanf("%d", &lines);

  for (int i = 0; i < lines * 2; ++i)
  {
    int personIndex;
    scanf("%d", &personIndex);
    if (womanMap.count(personIndex) == 0)
    {
      int *prefList = new int[lines + 1];
      womanMap[personIndex] = prefList;
      for (int j = 0; j < lines; ++j)
      {
        int preference;
        scanf("%d", &preference);
        prefList[preference] = j + 1;
      }
    }
    else
    {
      int *currentList = new int[lines];
      manMap[personIndex] = currentList;
      for (int j = 0; j < lines; ++j)
      {
        int preference;
        scanf("%d", &preference);
        currentList[j] = preference;
      }
    }
  }

  auto startRun = std::chrono::system_clock::now();

  GS(&manMap, &womanMap, &matchings);

  auto endRun = std::chrono::system_clock::now();

  std::chrono::duration<double> timeRun = endRun - startRun;

  std::map<int, int> sortedMatchings;

  for (std::unordered_map<int, int>::iterator it = matchings.begin(); it != matchings.end(); ++it)
  {
    sortedMatchings[it->first] = it->second;
  }
  for (std::map<int, int>::iterator it = sortedMatchings.begin(); it != sortedMatchings.end(); ++it)
  {
    std::cout << it->second << std::endl;
  }
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> time = end - start;

  //std::cout << "Computation took " << timeRun.count() << "s" << std::endl;

  //std::cout << "Program run took in total " << time.count() << "s" << std::endl;
}