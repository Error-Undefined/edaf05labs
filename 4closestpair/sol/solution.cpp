#include <iostream>
#include <algorithm>

struct point
{
  int x, y;
};

double dist(point *p1, point *p2)
{
  long xx = (p2->x - p1->x) * (p2->x - p1->x);
  long yy = (p2->y - p1->y) * (p2->y - p1->y);
  return sqrt(xx + yy);
}

double min(double d1, double d2)
{
  return (d1 < d2) ? d1 : d2;
}

double bruteForce(point **yArray, int points)
{
  double distance01 = dist(yArray[0], yArray[1]);

  if (points == 2)
  {
    return distance01;
  }

  double distance12 = dist(yArray[1], yArray[2]);
  double distance20 = dist(yArray[2], yArray[0]);

  return min(min(distance01, distance12), distance20);
}

double closestRecursive(point **xArray, point **yArray, int points)
{
  if (points < 4)
  {
    return bruteForce(yArray, points);
  }

  int midIndex = (points + 1) / 2;
  point *midPoint = xArray[midIndex];

  point *yLeft[midIndex];
  point *yRight[points - midIndex];

  int leftIndex = 0;
  int rightIndex = 0;

  for (int i = 0; i < points; i++)
  {
    if (yArray[i]->x <= midPoint->x && leftIndex < midIndex)
    {
      yLeft[leftIndex++] = yArray[i];
    }
    else
    {
      yRight[rightIndex++] = yArray[i];
    }
  }

  double dL = closestRecursive(xArray, yLeft, midIndex);
  double dR = closestRecursive(xArray + midIndex, yRight, points - midIndex);

  double delta = min(dL, dR);
}

int main()
{
  int points;

  std::cin >> points;

  point *xArray[points];
  point *yArray[points];

  for (int i = 0; i < points; i++)
  {
    int x, y;

    std::cin >> x;
    std::cin >> y;

    point *p = new point;
    p->x = x;
    p->y = y;

    xArray[i] = p;
    yArray[i] = p;
  }

  std::sort(xArray, xArray + points, [](point *p1, point *p2) { return p1->x < p2->x; });
  std::sort(yArray, yArray + points, [](point *p1, point *p2) { return p1->y < p2->y; });

  double result = 0;

  std::cout << result << std::endl;
}