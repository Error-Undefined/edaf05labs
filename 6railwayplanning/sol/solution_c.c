#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int preflow_push(int **capacities, int **flows, int source, int sink, int nodes)
{
  int *height = calloc(nodes, sizeof(int));
  int *excess = calloc(nodes, sizeof(int));

  height[source] = nodes;
  excess[source] = INT_MAX;

  for (int i = 0; i < nodes; i++)
  {
    if (i != source)
    {
      flows[source][i] = capacities[source][i];
      flows[i][source] = capacities[i][source];
    }
  }

  for (int i = 0; i < nodes; i++)
  {
    for (int j = 0; j < nodes; j++)
    {
      printf("%d  ", capacities[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for (int i = 0; i < nodes; i++)
  {
    for (int j = 0; j < nodes; j++)
    {
      printf("%d  ", flows[i][j]);
    }
    printf("\n");
  }
}

int main()
{
  int N, M, C, P;

  scanf("%d %d %d %d\n", &N, &M, &C, &P);

  int **flows, **graph, **edges;
  flows = calloc(N, sizeof(int *));
  graph = calloc(N, sizeof(int *));
  edges = calloc(2, sizeof(int *));
  edges[0] = calloc(M, sizeof(int));
  edges[1] = calloc(M, sizeof(int));

  for (int i = 0; i < N; i++)
  {
    flows[i] = calloc(N, sizeof(int));
    graph[i] = calloc(N, sizeof(int));
  }

  for (int i = 0; i < M; i++)
  {
    int u, v, c;
    scanf("%d %d %d\n", &u, &v, &c);
    graph[u][v] = c;
    graph[v][u] = c;

    edges[0][i] = u;
    edges[1][i] = v;
  }

  for (int i = 0; i < M; i++)
  {
    printf("%d-%d\n", edges[0][i], edges[1][i]);
  }

  /* 
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d  ", graph[i][j]);
    }
    printf("\n");
  }
  */

  int *to_remove = calloc(P, sizeof(int));
  for (int i = 0; i < P; i++)
  {
    scanf("%d\n", &to_remove[i]);
  }

  int ur = edges[0][to_remove[0]];
  int vr = edges[1][to_remove[0]];

  graph[ur][vr] = 0;
  graph[vr][ur] = 0;

  ur = edges[0][to_remove[1]];
  vr = edges[1][to_remove[1]];

  graph[ur][vr] = 0;
  graph[vr][ur] = 0;

  preflow_push(graph, flows, 0, N - 1, N);

  /*
  for (int i = 0; i < P; i++)
  {
    printf("%d\n", to_remove[i]);
  }
  */
}