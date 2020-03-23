#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>

bool womanPrefers(std::vector<int> *prefList, int currentMan, int newMan)
{
  int currentManIndex = -1;
  int newManIndex = -1;
  int counter = 0;
  for (std::vector<int>::iterator it = prefList->begin(); it != prefList->end(); ++it)
  {
    if (*it == currentMan)
    {
      currentManIndex = counter;
    }
    else if (*it == newMan)
    {
      newManIndex = counter;
    }

    if (newManIndex >= 0 && currentManIndex >= 0)
    {
      break;
    }

    ++counter;
  }
  return newManIndex < currentManIndex;
}

void GS(std::map<int, std::vector<int> *> *manMap, std::map<int, std::vector<int> *> *womanMap, std::map<int, int> *matchings, int couples)
{
  std::vector<int> manList;
  std::map<int, int> manProposals;
  for (int i = 0; i < couples; ++i)
  {
    manList.push_back(i + 1);
    manProposals[i + 1] = 0;
  }

  while (manList.size() > 0)
  {
    int man = manList.front();
    manList.erase(manList.begin());
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

void printMap(std::map<int, std::vector<int> *> manMap, std::map<int, std::vector<int> *> womanMap)
{
  for (std::map<int, std::vector<int> *>::iterator it = manMap.begin(); it != manMap.end(); ++it)
  {
    std::cout << "Man " << it->first << ":";
    std::vector<int> *prefList = it->second;
    for (std::vector<int>::iterator vecIt = prefList->begin(); vecIt != prefList->end(); ++vecIt)
    {
      std::cout << *vecIt << " ";
    }
    std::cout << std::endl;
  }

  for (std::map<int, std::vector<int> *>::iterator it = womanMap.begin(); it != womanMap.end(); ++it)
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

  std::map<int, std::vector<int> *> manMap;
  std::map<int, std::vector<int> *> womanMap;
  std::map<int, int> matchings;

  // scan data
  int lines;
  scanf("%d", &lines);

  for (int i = 0; i < lines * 2; ++i)
  {
    int personIndex;
    std::vector<int> *currentList = new std::vector<int>;
    scanf("%d", &personIndex);
    if (womanMap.count(personIndex) == 0)
    {
      womanMap[personIndex] = currentList;
    }
    else
    {
      manMap[personIndex] = currentList;
    }
    for (int j = 0; j < lines; ++j)
    {
      int preference;
      scanf("%d", &preference);
      currentList->push_back(preference);
    }
  }

  GS(&manMap, &womanMap, &matchings, lines);

  for (std::map<int, int>::iterator it = matchings.begin(); it != matchings.end(); ++it)
  {
    std::cout << it->second << std::endl;
  }
}