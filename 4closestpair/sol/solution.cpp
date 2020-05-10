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