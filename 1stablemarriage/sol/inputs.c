#include <stdio.h>

void main(int argc, char** argv)
{
  int lines;
  scanf("%d", &lines);

  for(int i = 0; i < 2*lines; i++){
    for(int j = 0; j < 2*lines - 1; j++){
      char in[100];
      scanf("%s", in);
      printf("%s ", in);
    }
    printf("\n");
  }
}