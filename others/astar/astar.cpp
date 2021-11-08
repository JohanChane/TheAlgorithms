#include <iostream>
#include <cfloat>
#include <set>
#include <cstring>

#include "astar.h"

using namespace std;

typedef Cell (*CellDetails)[COL];
typedef const Cell (*ConstCellDetails)[COL];

static Path tracePath(const Point& dest, ConstCellDetails cellDetails);
static void printPath(Path path);
static bool operator==(const Point& a, const Point& b);

static inline double calculateH(const Point& point, const Point& dest);
static inline double calculateG(double g, double distance);
static inline double calculateF(double h, double g);

static inline bool isValid(const Point& point);
static inline bool isUnBlocked(const Point& point, ConstGrid grid);

Path aStarSearch(const Point& src, const Point& dest, ConstGrid grid) {
    if (!isValid(src) || !isValid(dest)) {
        cerr << "src or dest isn't valid.\n";
        exit(EXIT_FAILURE);
    }

    if (!isUnBlocked(src, grid) || !isUnBlocked(src, grid)) {
        cerr << "Source or the destination is blocked\n";
        exit(EXIT_FAILURE);
    }

    if (src.first == dest.first && src.first == dest.second) {
        Path path;
        path.push(dest);
        return path;
    }

    Cell cellDetails[ROW][COL];

    // ### initilize cellDetails
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            cellDetails[x][y].parent.first = -1;
            cellDetails[x][y].parent.first = -1;
            cellDetails[x][y].h = DBL_MAX;
            cellDetails[x][y].g = DBL_MAX;
            cellDetails[x][y].f = DBL_MAX;
        }
    }

    // ### 源点的父点是本身
    cellDetails[src.first][src.second].parent.first = src.first;
    cellDetails[src.first][src.second].parent.second = src.second;
    cellDetails[src.first][src.second].h = 0.0;
    cellDetails[src.first][src.second].g = 0.0;
    cellDetails[src.first][src.second].f = 0.0;

    // openList 存放还没有走过且可以通过的点
    set<FPoint> openList;
    // 将源点加入 openList
    openList.insert(make_pair(0.0, src));

    // closeList 存放已走过的点
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof (closedList));

    FPoint fpoint;
    Point point;
    Point epoint, wpoint, npoint, spoint, nepoint, nwpoint, sepoint, swpoint;
    double gNew, hNew, fNew;
    while (!openList.empty()) {
        // ### 找出 f 最小的点
        fpoint = *openList.begin(); openList.erase(openList.begin());

        point = fpoint.second;

        // ### 走到此点
        closedList[point.first][point.second] = true;

        // ## 处理相邻点
        // ### east point
        epoint = make_pair(point.first + 1, point.second);
        if (isValid(epoint)) {
            if (epoint == dest) {
                cellDetails[epoint.first][epoint.second].parent = point;
                break;
            } else if (!closedList[epoint.first][epoint.second] && isUnBlocked(epoint, grid)) {
				hNew = calculateH(epoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.0;
				fNew = gNew + hNew;

				if (cellDetails[epoint.first][epoint.second].f > fNew) {
					openList.insert(make_pair(fNew, epoint));

					cellDetails[epoint.first][epoint.second].f = fNew;
					cellDetails[epoint.first][epoint.second].g = gNew;
					cellDetails[epoint.first][epoint.second].h = hNew;
					cellDetails[epoint.first][epoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### west point
        wpoint = make_pair(point.first - 1, point.second);
        if (isValid(wpoint)) {
            if (wpoint == dest) {
                cellDetails[wpoint.first][wpoint.second].parent = point;
                break;
            } else if (!closedList[wpoint.first][wpoint.second] && isUnBlocked(wpoint, grid)) {
				hNew = calculateH(wpoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.0;
				fNew = gNew + hNew;

				if (cellDetails[wpoint.first][wpoint.second].f > fNew) {
					openList.insert(make_pair(fNew, wpoint));

					cellDetails[wpoint.first][wpoint.second].f = fNew;
					cellDetails[wpoint.first][wpoint.second].g = gNew;
					cellDetails[wpoint.first][wpoint.second].h = hNew;
					cellDetails[wpoint.first][wpoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### north point
        npoint = make_pair(point.first, point.second + 1);
        if (isValid(npoint)) {
            if (npoint == dest) {
                cellDetails[npoint.first][npoint.second].parent = point;
                break;
            } else if (!closedList[npoint.first][npoint.second] && isUnBlocked(npoint, grid)) {
				hNew = calculateH(npoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.0;
				fNew = gNew + hNew;

				if (cellDetails[npoint.first][npoint.second].f > fNew) {
					openList.insert(make_pair(fNew, npoint));

					cellDetails[npoint.first][npoint.second].f = fNew;
					cellDetails[npoint.first][npoint.second].g = gNew;
					cellDetails[npoint.first][npoint.second].h = hNew;
					cellDetails[npoint.first][npoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### south point
        spoint = make_pair(point.first, point.second - 1);
        if (isValid(spoint)) {
            if (spoint == dest) {
                cellDetails[spoint.first][spoint.second].parent = point;
                break;
            } else if (!closedList[spoint.first][spoint.second] && isUnBlocked(spoint, grid)) {
				hNew = calculateH(spoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.0;
				fNew = gNew + hNew;

				if (cellDetails[spoint.first][spoint.second].f > fNew) {
					openList.insert(make_pair(fNew, spoint));

					cellDetails[spoint.first][spoint.second].f = fNew;
					cellDetails[spoint.first][spoint.second].g = gNew;
					cellDetails[spoint.first][spoint.second].h = hNew;
					cellDetails[spoint.first][spoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### north east point
        nepoint = make_pair(point.first + 1, point.second + 1);
        if (isValid(nepoint)) {
            if (nepoint == dest) {
                cellDetails[nepoint.first][nepoint.second].parent = point;
                break;
            } else if (!closedList[nepoint.first][nepoint.second] && isUnBlocked(nepoint, grid)) {
				hNew = calculateH(nepoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.414;
				fNew = gNew + hNew;

				if (cellDetails[nepoint.first][nepoint.second].f > fNew) {
					openList.insert(make_pair(fNew, nepoint));

					cellDetails[nepoint.first][nepoint.second].f = fNew;
					cellDetails[nepoint.first][nepoint.second].g = gNew;
					cellDetails[nepoint.first][nepoint.second].h = hNew;
					cellDetails[nepoint.first][nepoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### north west point
        nwpoint = make_pair(point.first - 1, point.second + 1);
        if (isValid(nwpoint)) {
            if (nwpoint == dest) {
                cellDetails[nwpoint.first][nwpoint.second].parent = point;
                break;
            } else if (!closedList[nwpoint.first][nwpoint.second] && isUnBlocked(nwpoint, grid)) {
				hNew = calculateH(nwpoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.414;
				fNew = gNew + hNew;

				if (cellDetails[nwpoint.first][nwpoint.second].f > fNew) {
					openList.insert(make_pair(fNew, nwpoint));

					cellDetails[nwpoint.first][nwpoint.second].f = fNew;
					cellDetails[nwpoint.first][nwpoint.second].g = gNew;
					cellDetails[nwpoint.first][nwpoint.second].h = hNew;
					cellDetails[nwpoint.first][nwpoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### south east point
        sepoint = make_pair(point.first + 1, point.second - 1);
        if (isValid(sepoint)) {
            if (sepoint == dest) {
                cellDetails[sepoint.first][sepoint.second].parent = point;
                break;
            } else if (!closedList[sepoint.first][sepoint.second] && isUnBlocked(sepoint, grid)) {
				hNew = calculateH(sepoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.414;
				fNew = gNew + hNew;

				if (cellDetails[sepoint.first][sepoint.second].f > fNew) {
					openList.insert(make_pair(fNew, sepoint));

					cellDetails[sepoint.first][sepoint.second].f = fNew;
					cellDetails[sepoint.first][sepoint.second].g = gNew;
					cellDetails[sepoint.first][sepoint.second].h = hNew;
					cellDetails[sepoint.first][sepoint.second].parent = point;
				}
            } else {
                ;
            }
        }

        // ### south west point
        sepoint = make_pair(point.first - 1, point.second - 1);
        if (isValid(sepoint)) {
            if (sepoint == dest) {
                cellDetails[sepoint.first][sepoint.second].parent = point;
                break;
            } else if (!closedList[sepoint.first][sepoint.second] && isUnBlocked(sepoint, grid)) {
				hNew = calculateH(sepoint, dest);
				gNew = cellDetails[point.first][point.second].g + 1.414;
				fNew = gNew + hNew;

				if (cellDetails[sepoint.first][sepoint.second].f > fNew) {
					openList.insert(make_pair(fNew, sepoint));

					cellDetails[sepoint.first][sepoint.second].f = fNew;
					cellDetails[sepoint.first][sepoint.second].g = gNew;
					cellDetails[sepoint.first][sepoint.second].h = hNew;
					cellDetails[sepoint.first][sepoint.second].parent = point;
				}
            } else {
                ;
            }
        }
    }

    return tracePath(dest, cellDetails);
}

static Path tracePath(const Point& dest, ConstCellDetails cellDetails) {
	stack<Point> path;

    Point point = dest;

    // 源点的父点是本身
    while (!(cellDetails[point.first][point.second].parent == point)) {
        path.push(point);
        point = cellDetails[point.first][point.second].parent;
    }

    // 将 src 加入路径中
	path.push(point);

	return path;
}

static void printPath(Path path) {
    Point point;
    while (!path.empty()) {
        point = path.top(); path.pop();
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << endl;
}

static inline double calculateH(const Point& point, const Point& dest) {
    return pow(pow(point.first - dest.first, 2) + pow(point.second - dest.second, 2), 0.5);
}

static inline double calculateG(double g, double distance) {
    return g + distance;
}

static inline double calculateF(double h, double g) {
    return h + g;
}

static inline bool isValid(const Point& point) {
    return (point.first >= 0 && point.first < ROW)
            && (point.second >= 0 && point.second < COL);
}

static inline bool isUnBlocked(const Point& point, ConstGrid grid) {
    return grid[point.first][point.second] == 1;
}

static bool operator==(const Point& a, const Point& b) {
    return (a.first == b.first && a.second == b.second);
}

int main() {
	// 1: The cell is not blocked
    // 0: The cell is blocked
	int grid[ROW][COL] = {  { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }};

	Point src = make_pair(8, 0);
	Point dest = make_pair(0, 0);
	Path path = aStarSearch(src, dest, grid);
    printPath(path);

    src = make_pair(0, 0);
    dest = make_pair(8, 0);
    path = aStarSearch(src, dest, grid);
    printPath(path);

    return 0;
}

