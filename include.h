#ifndef SNAKE_GAME_INCLUDE_H
#define SNAKE_GAME_INCLUDE_H

#include <vector>

// consts
#define KILL_SNAKE -1
#define SKIP_TURN -2
#define SNAKE_KILLED -5


// structs
typedef struct coords {
    int x;
    int y;
} coords;

// Forward declaration
class Map;

// finctions
// coords random_direction();

// classes
class Snake {
public:
    Snake(int x, int y, Map* map);

    int move(int xd, int yd);
    coords pick_direction();
    void grow();
    int is_boundary(int xd, int yd);
    void find_food(int xd, int yd);


    ~Snake();

    std::vector<coords> snake_coords;
    coords forward;

    Map* map;

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

    int n, m; // size of map, can be static
    std::vector<Snake*> snakes;
    std::vector<coords> food;

    std::vector< std::vector<std::string> > field; // map
};


#endif //SNAKE_GAME_INCLUDE_H
