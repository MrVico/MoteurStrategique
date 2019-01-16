#include "point.h"

Point::Point(int a, int b) {
    x = a;
    y = b;
}

bool Point::operator==(const Point& p) {
    if(p.x == x && p.y == y)
        return true;

    else return false;
}

Point Point::operator+(const Point& p) {
    return Point(p.x + x, p.y + y);
}
