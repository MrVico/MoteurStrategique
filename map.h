#ifndef MAP_H
#define MAP_H

#include <iostream>

class map
{
public:
    int w = 1080;
    int h = 720;

    int m[1080][720] = {{0}};

    void addObstacle(int x, int y) {
        //en haut a gauche
        for(int i = x; i < x + 32; ++i) {
            for(int j = y; j < y + 32; ++j) {
                m[i][j] = 1;
            }
        }
    }

    void printMap() {
        for(int i = 0; i < w; ++i) {
            for(int j = 0; j < h; ++j) {
                std::cout << m[i][j];
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void setMap(int map[1080][720]) {
        for(int i = 0; i < w; ++i) {
            for(int j = 0; j < h; ++j) {
                m[i][j] = map[i][j];
            }
        }
    }

    int operator() ( int x, int y ) { return m[x][y]; }
};

#endif // MAP_H
