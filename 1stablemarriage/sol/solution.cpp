#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <stdio.h>
#include <list>

bool womanPrefers(int *prefList, int currentMan, int newMan)
{
  return prefList[newMan] < prefList[currentMan];
}

void GS(std::unordered_map<int, std::vector<int> *> *manMap, std::unordered_map<int, int *> *womanMap, std::unordered_map<int, int> *matchings, int couples)
{
  std::list<int> manList;
  std::unordered_map<int, int> manProposals;
  for (int i = 0; i < couples; ++i)
  {
    manList.push_back(i + 1);
    manProposals[i + 1] = 0;
  }

  while (manList.size() > 0)
  {
    int man = manList.front();
    manList.pop_front();
    std::vector<int> *prefList = (*manMap)[man];
    int woman = prefList->at(manProposals[man]);
    manProposals[man]++;

    if (matchings->count(woman) == 0)
    {
      (*matchings)[woman] = man;
    }
    else if (womanPrefers(womanMap->at(woman), (*matchings)[woman], man))
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

void printMap(std::unordered_map<int, std::vector<int> *> manMap, std::unordered_map<int, std::vector<int> *> womanMap)
{
  for (std::unordered_map<int, std::vector<int> *>::iterator it = manMap.begin(); it != manMap.end(); ++it)
  {
    std::cout << "Man " << it->first << ":";
    std::vector<int> *prefList = it->second;
    for (std::vector<int>::iterator vecIt = prefList->begin(); vecIt != prefList->end(); ++vecIt)
    {
      std::cout << *vecIt << " ";
    }
    std::cout << std::endl;
  }

  for (std::unordered_map<int, std::vector<int> *>::iterator it = womanMap.begin(); it != womanMap.end(); ++it)
  {
    std::cout << "Woman " << it->first << ":";
    std::vector<int> *prefList = it->second;
    for (std::vector<int>::iterator vecIt = prefList->begin(); vecIt != prefList->end(); ++vecIt)
    {
      std::cout << *vecIt << " ";
    }
    std::cout << std::endl;
  }
}

int main()
{

  std::unordered_map<int, std::vector<int> *> manMap;
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
      std::vector<int> *currentList = new std::vector<int>;
      manMap[personIndex] = currentList;
      for (int j = 0; j < lines; ++j)
      {
        int preference;
        scanf("%d", &preference);
        currentList->push_back(preference);
      }
    }
  }

  //std::cout << "Finished reading\n";

  GS(&manMap, &womanMap, &matchings, lines);

  std::map<int, int> sortedMatchings;

  for (std::unordered_map<int, int>::iterator it = matchings.begin(); it != matchings.end(); ++it)
  {
    sortedMatchings[it->first] = it->second;
  }
  for (std::map<int, int>::iterator it = sortedMatchings.begin(); it != sortedMatchings.end(); ++it)
  {
    std::cout << it->second << std::endl;
  }
}