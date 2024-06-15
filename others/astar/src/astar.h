#ifndef ASTAR_H
#define ASTAR_H

#include <utility>
#include <cmath>
#include <stack>

const int ROW = 9;
const int COL = 10;

typedef std::pair<int, int> Point;
typedef std::pair<double, Point> FPoint;
typedef std::stack<Point> Path;
typedef int (*Grid)[COL];
typedef const int (*ConstGrid)[COL];

struct Cell {
    Point parent;
    double h, g, f;
};

Path aStarSearch(const Point& src, const Point& dest, ConstGrid grid);

#endif
