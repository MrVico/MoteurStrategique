#include "map.h"

#include <iostream>

// Put 1 for each pixel of the obstacle
void Map::addObstacle(int x, int y) {
    //Coord start on top left and the obstacle's sprite is 32x32
    for(int i = x; i < x + 32; ++i) {
        for(int j = y; j < y + 32; ++j) {
            m[i][j] = 1;
        }
    }
}

void Map::printMap() {
    for(int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j) {
            std::cout << m[i][j];
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Map::setMap(int map[1080][720]) {
    for(int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j) {
            m[i][j] = map[i][j];
        }
    }
}

int Map::getVal(int x, int y) {
    return m[x][y];
}
