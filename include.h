#ifndef SNAKE_GAME_INCLUDE_H
#define SNAKE_GAME_INCLUDE_H

#include <vector>

// structs
typedef struct coords {
    int x;
    int y;
} coords;

// Forward declaration
class Map;

// classes
class Snake {
public:
    Snake(int x, int y, int length, Map* map);
    void move();
    ~Snake();

    int x, y; // head's location on the map
    std::vector<coords> snake_coords;

    Map* map;

    int length;
};

/*
class Food {
public:
    Food(int x, int y);
    ~Food();

    int size;
};
*/

class Map {
public:
    Map(int n, int m);
    void print();

    int n, m; // size of map
    std::vector<Snake*> snakes;
    std::vector< std::vector<std::string> > field; // map
};


#endif //SNAKE_GAME_INCLUDE_H
