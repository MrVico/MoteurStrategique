#ifndef POINT_H
#define POINT_H


class Point
{
public:
    int x;
    int y;

    Point(int a = 0, int b = 0);

    bool operator==(const Point& p);
    Point operator+(const Point& p);
};

#endif // POINT_H
