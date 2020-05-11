#include <iostream>
#include <algorithm>

#define DOUBLE_INFINITY 1e+20f

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

double absValue(double d)
{
  return (d > 0) ? d : -d;
}

double bruteForce(point **xArray, int points)
{
  if (points == 2)
  {
    return dist(xArray[0], xArray[1]);
  }

  double minDistance = DOUBLE_INFINITY;
  for (int i = 0; i < points; i++)
  {
    for (int j = i + 1; j < points; j++)
    {
      double temp = dist(xArray[i], xArray[j]);
      minDistance = min(minDistance, temp);
    }
  }

  return minDistance;
}

double closestRecursive(point **xArray, point **yArray, int points)
{
  if (points < 4)
  {
    return bruteForce(xArray, points);
  }

  int midIndex = (points + 1) / 2;
  point *midPoint = xArray[midIndex];

  point **yLeft = new point *[midIndex];
  point **yRight = new point *[points - midIndex];

  point **xLeft = new point *[midIndex];
  point **xRight = new point *[points - midIndex];

  for (int i = 0; i < midIndex; i++)
  {
    xLeft[i] = xArray[i];
  }
  for (int i = 0; i < points - midIndex; i++)
  {
    xRight[i] = xArray[i + midIndex];
  }

  int leftI = 0;
  int rightI = 0;
  for (int i = 0; i < points; i++)
  {
    if (yArray[i]->x <= midPoint->x && leftI < midIndex)
    {
      yLeft[leftI++] = yArray[i];
    }
    else if (rightI < points - midIndex)
    {
      yRight[rightI++] = yArray[i];
    }
    else
    {
      yLeft[leftI] = yArray[i];
    }
  }

  double dL = closestRecursive(xLeft, yLeft, midIndex);
  double dR = closestRecursive(xRight, yRight, points - midIndex);

  double delta = min(dL, dR);

  std::vector<point *> closeToMiddle;
  for (int i = 0; i < points; i++)
  {
    if (absValue(yArray[i]->x - midPoint->x) < delta)
    {
      closeToMiddle.push_back(yArray[i]);
    }
  }

  double smallestInMiddle = DOUBLE_INFINITY;
  for (int i = 0; i < closeToMiddle.size(); i++)
  {
    for (int j = i + 1; j < closeToMiddle.size() && j < i + 15; j++)
    {
      double tempDistance = dist(closeToMiddle[i], closeToMiddle[j]);
      smallestInMiddle = min(smallestInMiddle, tempDistance);
    }
  }

  return min(delta, smallestInMiddle);
}

int main()
{
  int points;

  std::cin >> points;

  point **xArray = new point *[points];
  point **yArray = new point *[points];

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

  double result = closestRecursive(xArray, yArray, points);

  std::cout << result << std::endl;
}