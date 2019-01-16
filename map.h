#ifndef MAP_H
#define MAP_H

class Map {
public:
    int w = 1080;
    int h = 720;

    int m[1080][720] = {{0}};

    void addObstacle(int x, int y);

    void printMap();

    void setMap(int map[1080][720]);

    int getVal(int x, int y);
};

#endif // MAP_H
