#include "astar.h"

#include <iostream>

// Initialise the coord of the 8 neighbours
AStar::AStar() {
    neighbours[0] = Point( -1, -1 );
    neighbours[1] = Point(  1, -1 );
    neighbours[2] = Point( -1,  1 );
    neighbours[3] = Point(  1,  1 );
    neighbours[4] = Point(  0, -1 );
    neighbours[5] = Point( -1,  0 );
    neighbours[6] = Point(  0,  1 );
    neighbours[7] = Point(  1,  0 );
}

// Compute the distance between current Point p and the end point with an heuristic
int AStar::calcDist(Point& p) {
    //std::cout << "calcDist" << std::endl;

    int x = end.x - p.x;
    int y = end.y - p.y;

    int dist = x * x + y * y;

    return dist;
}

// Return false if the current Point p is an obstacle, else return true
bool AStar::isValid(Point& p) {
    //std::cout << "isValid" << std::endl;

    if (p.x >-1 && p.y > -1 && p.x < map.w && p.y < map.h)
        return true;

    else return false;
}

// Search Point p with cost in open and closed list
bool AStar::existPoint(Point& p, int cost) {
    //std::cout << "existPoint" << std::endl;

    std::list<Node>::iterator i;

    i = std::find(closed.begin(), closed.end(), p);
    if(i != closed.end()) {
        if((*i).cost + (*i).dist < cost)
            return true;
        else {
            closed.erase(i);
            return false;
        }
    }

    i = std::find(open.begin(), open.end(), p);
    if(i != open.end()) {
        if((*i).cost + (*i).dist < cost)
            return true;
        else {
            open.erase(i);
            return false; }
    }

    return false;
}

// Fill the open list with new candidate
bool AStar::fillOpen(Node& n) {
    //std::cout << "fillOpen" << std::endl;

    int nc;
    int dist;
    Point neighbour;

    for(int x = 0; x < 8; ++x) {
        neighbour = n.pos + neighbours[x];

        if(neighbour == end)
            return true;

        if(isValid(neighbour) && map.getVal(neighbour.x, neighbour.y) != 1) {
            nc = n.cost + 1;
            dist = calcDist(neighbour);
            if(!existPoint(neighbour, nc + dist)) {
                Node m;
                m.cost = nc;
                m.dist = dist;
                m.pos = neighbour;
                m.parent = n.pos;

                open.push_back(m);
            }
        }
    }
    return false;
}

// Run A* algorithm
bool AStar::search(Point& s, Point& e, Map& m) {
    //std::cout << "Search" << std::endl;

    Node n;
    end = e;
    start = s;
    map = m;
    n.cost = 0;
    n.pos = s;
    n.parent = 0;
    n.dist = calcDist(s);

    open.push_back( n );
    while(!open.empty()) {
        //open.sort();
        Node n = open.front();
        open.pop_front();
        closed.push_back(n);
        if(fillOpen(n))
            return true;
    }
    return false;
}

// Fill the path list with the result's coords of A*
int AStar::path(std::list<Point>& path) {
    //std::cout << "path" << std::endl;

    path.push_front(end);
    int cost = 1 + closed.back().cost;
    path.push_front(closed.back().pos);
    Point parent = closed.back().parent;

    for(std::list<Node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); ++i) {
        if((*i).pos == parent && !((*i).pos == start)) {
            path.push_front((*i).pos );
            parent = (*i).parent;
        }
    }
    path.push_front(start);

    return cost;
}
