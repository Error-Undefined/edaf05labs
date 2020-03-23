#include <iostream>
#include <stdio.h>
#include <vector>

int main(int argc, char **argv)
{
  int lines;
  scanf("%d", &lines);

  std::cout << "There are " << 2 * lines << " lines of data" << std::endl;

  for (int i = 0; i < 2 * lines; i++)
  {
    for (int j = 0; j < 2 * lines - 1; j++)
    {
      int in;
      scanf("%d ", &in);
      std::cout << in;
    }
    std::cout << std::endl;
  }
}