#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include "map.h"

#include <algorithm>
#include <list>

class AStar {
public:
    Map map;

    Point end;
    Point start;
    Point neighbours[8];

    std::list<Node> open;
    std::list<Node> closed;

    AStar();

    int calcDist(Point& p);

    bool isValid(Point& p);

    bool existPoint(Point& p, int cost);

    bool fillOpen(Node& n);

    bool search(Point& s, Point& e, Map& m);

    int path(std::list<Point>& path);
};

#endif // ASTAR_H
