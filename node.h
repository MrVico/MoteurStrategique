#ifndef NODE_H
#define NODE_H

#include "point.h"

class Node {
public:
    int dist;
    int cost;

    Point pos;
    Point parent;

    bool operator==(const Node& n);
    bool operator==(const Point& p);
    bool operator<(const Node& n);
};

#endif // NODE_H
