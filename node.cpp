#include "node.h"


bool Node::operator==(const Node& n) {
    return pos == n.pos;
}

bool Node::operator==(const Point& p) {
    return pos == p;
}

bool Node::operator<(const Node& n) {
    return dist + cost < n.dist + n.cost;
}
