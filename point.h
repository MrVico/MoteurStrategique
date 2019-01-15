#ifndef POINT_H
#define POINT_H


class point
{
public:
    int x;
    int y;

    point( int a = 0, int b = 0 ) { x = a; y = b; }

    bool operator ==( const point& o ) { return o.x == x && o.y == y; }
    point operator +( const point& o ) { return point( o.x + x, o.y + y ); }
};

#endif // POINT_H
