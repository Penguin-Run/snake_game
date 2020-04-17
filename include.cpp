#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "include.h"
#include <time.h>

// functions
coords Snake::pick_direction() {
    /*
    int x, y;
    int direction = rand() % 4 + 1;
    switch(direction) {
        case 1:
            // moving right
            x = 0; y = 1;
            break;
        case 2:
            // moving left
            x = 0; y = -1;
            break;
        case 3:
            // moving down
            x = 1; y = 0;
            break;
        case 4:
            // moving up
            x = -1; y = 0;
            break;
        default:
            x = 1; y = 0;
    }

    return {x, y};
     */

    // if forward is not empty
    if (!((forward.x == 0) && (forward.y == 0))) {
        int is_forward = rand() % 8; // chance to change direction - 1/4
        if (!is_forward) {
            // change direction
            // forward direction was right or left
            if (!forward.x) {
                forward.y = 0;
                if (rand() % 2) {
                    forward.x = 1; // down
                } else {
                    forward.x = -1; // up
                }
            }
            // forward direction was up or down
            else if (!forward.y) {
                forward.x = 0;
                if (rand() % 2) {
                    forward.y = 1; // right
                } else {
                    forward.y = -1; // left
                }
            }
        }
    }
    // forward is empty - get random direction
    else {
        int direction = rand() % 4 + 1;
        switch(direction) {
            case 1:
                // moving right
                forward.x = 0; forward.y = 1;
                break;
            case 2:
                // moving left
                forward.x = 0; forward.y = -1;
                break;
            case 3:
                // moving down
                forward.x = 1; forward.y = 0;
                break;
            case 4:
                // moving up
                forward.x = -1; forward.y = 0;
                break;
            default:
                forward.x = 1; forward.y = 0;
        }
    }

    return forward;
}

// class methods
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

        food.push_back({x, y});
    }

    // snakes
    for(int i = 0; i < (rand() % 10 + 4); i++) {
        int x = rand() % n; // location
        int y = rand() % m; // location

        snakes.push_back(new Snake(x, y, this));
    }

}

void Map::print() {
    // clearing field
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            field[i][j] = " ";
        }
    }

    // draw food on the field
    for (int i = 0; i < food.size(); i++) {
        field[food[i].x][food[i].y] = "*";
    }

    // draw snakes on the field
    for (int i = 0; i < snakes.size(); i++) {
        for (int j = 0; j < snakes[i]->snake_coords.size(); j++) {
            // if it's head of the snake (first coords in vector) then "■" else "□"
            if (j == 0) {
                field[snakes[i]->snake_coords[j].x][snakes[i]->snake_coords[j].y] = "■";
            } else {
                field[snakes[i]->snake_coords[j].x][snakes[i]->snake_coords[j].y] = "□";
            }
        }
    }


    // printing field to the console
    for (int i = 0; i < m*2+2; i++) std::cout << "_";
    std::cout << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << "|";
        for (int j = 0; j < m; j++) {
            std::cout << field[i][j] << " ";
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    for (int i = 0; i < m*2+2; i++) std::cout << "_";
    std::cout << std::endl << std::endl << std::endl;

}


Snake::Snake(int x, int y, Map* map) {
    snake_coords.push_back({x, y});
    this->map = map;
    forward = {0, 0};
}

int Snake::move(int xd, int yd) {

    if (is_boundary(xd, yd) == KILL_SNAKE) {
        delete this;
        // should be removed from vector of pointers to all snakes in map !!!
        return SNAKE_KILLED;
    }

    // if this snake goes backwards or if snake goes out of bounds
    else if (is_boundary(xd, yd) == SKIP_TURN) {
        return 0;
    }

    // move body
    for (int i = (int)snake_coords.size() - 1; i > 0; i--) {
        snake_coords[i].x = snake_coords[i-1].x;
        snake_coords[i].y = snake_coords[i-1].y;
    }

    // if food was here - eat it
    find_food(xd, yd);

    // move head
    snake_coords[0].x += xd;
    snake_coords[0].y += yd;

    return 0;
}

int Snake::is_boundary(int xd, int yd) {
    int new_x = snake_coords[0].x + xd;
    int new_y = snake_coords[0].y + yd;

    // if snake goes out of bounds
    if ((new_x >= map->n) || (new_y >= map->m) || (new_x < 0) || (new_y < 0)){
        return SKIP_TURN;
    }

    // if snake goes back
    if ((new_x == snake_coords[1].x) && (new_y == snake_coords[1].y)) {
        return SKIP_TURN;
    }

    // if snake hits itself (except goes back)
    for (int i = 2; i < snake_coords.size(); i++) {
        if ((new_x == snake_coords[i].x) && (new_y == snake_coords[i].y)) {
            return SKIP_TURN;
        }
    }

    // if snake hits another snake
    for (int i = 0; i < map->snakes.size(); i++) {
        if (map->snakes[i] == this) continue; // !
        for (int j = 0; j < map->snakes[i]->snake_coords.size(); j++) {
            if ((new_x == map->snakes[i]->snake_coords[j].x)
            && (new_y == map->snakes[i]->snake_coords[j].y)) {
                return KILL_SNAKE;
            }
        }
    }

    return false;
}

void Snake::find_food(int xd, int yd) {
    int new_x = snake_coords[0].x + xd;
    int new_y = snake_coords[0].y + yd;

    for (int i = 0; i < map->food.size(); i++) {
        if ((new_x == map->food[i].x) && (new_y == map->food[i].y)) {
            grow();
            map->food.erase(map->food.begin() + i);
            return;
        }
    }
}

void Snake::grow() {
    // +1 piece of the snake
    int new_piece_x, new_piece_y;

    // check if new snake cell would grow on already existing snake cell
    if (snake_coords[snake_coords.size()-2].x == snake_coords[snake_coords.size()-1].x + 1) {
        new_piece_x = snake_coords[snake_coords.size()-1].x - 1;
        new_piece_y = snake_coords[snake_coords.size()-1].y;
    } else {
        new_piece_x = snake_coords[snake_coords.size()-1].x + 1;
        new_piece_y = snake_coords[snake_coords.size()-1].y;
    }

    // check if new piece would go out of the map boundaries
    if ((new_piece_x < map->n) && (new_piece_y < map->m)
    && (new_piece_x >= 0) && (new_piece_y >= 0)) {
        snake_coords.push_back({new_piece_x,new_piece_y});
    }

}

Snake::~Snake() {
    std::cout << "Snake Killed" << std::endl;
}
