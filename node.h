#ifndef NODE_H
#define NODE_H

#include "point.h"

class node
{
public:
    int dist;
    int cost;

    point pos;
    point parent;

    bool operator == (const node& o ) { return pos == o.pos; }
    bool operator == (const point& o ) { return pos == o; }
    bool operator < (const node& o ) { return dist + cost < o.dist + o.cost; }
};

#endif // NODE_H
