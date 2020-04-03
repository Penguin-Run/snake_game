#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "include.h"
#include <time.h>

// □

// CLASS METHODS
Map::Map(int n, int m) {
    this->n = n;
    this->m = m;

    srand(time(NULL));

    // creating  a game field
    for (int i = 0; i < n; i++) {
        field.push_back(std::vector<std::string>(m, " "));
    }

    // creating objects on the game field
    // food
    for(int i = 0; i < (rand() % n*m/10 + n*m/5); i++) {
        int x = rand() % n; // location
        int y = rand() % m; // location

        field[x][y] = "*";
    }

    // snakes
    for(int i = 0; i < (rand() % 6 + 2); i++) {
        int x = rand() % n; // location
        int y = rand() % m; // location

        snakes.push_back(new Snake(x, y, 1, this));
    }
}
void Map::print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


Snake::Snake(int x, int y, int length, Map* map) : x(x), y(y), length(length) {
    snake_coords.push_back({x, y});
    this->map = map;

    map->field[x][y] = "■"; // □
}
void Snake::move() {
    
}
Snake::~Snake() {
    std::cout << "Snake Killed" << std::endl;
}