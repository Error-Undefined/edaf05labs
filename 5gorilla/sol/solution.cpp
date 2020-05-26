#include <iostream>
#include <algorithm>

int main()
{
  std::string alphabet;
  std::getline(std::cin, alphabet);

  alphabet.erase(std::remove_if(alphabet.begin(), alphabet.end(), isspace), alphabet.end());

  int letters = alphabet.length();

  int costMatrix[2][2];
}