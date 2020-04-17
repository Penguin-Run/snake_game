#include <iostream>
#include "include.h"
#include <time.h>
#include <unistd.h>

/*
Bugs:
- snakes can spawn on the same cells as food: recreate spawning logic or create method, that would secure this problem (eat food if snake spawn there)


 Tasks:
 - Change direction if snake hit border
 - invent pausing every turn
 - balance snakes and craate food and snakes creation funcs

 - implement ncurses library
 */


int main() {
    Map map(30, 30);
    map.print();



    srand(time(NULL));

    bool run = true;
    while (!map.snakes.empty()) {
    // for (int j = 0; j < 100; j++) {
        for (int i = 0; i < map.snakes.size(); i++) {
            coords direction = map.snakes[i]->pick_direction();
            if (map.snakes[i]->move(direction.x, direction.y) == SNAKE_KILLED) {
                map.snakes.erase(map.snakes.begin() + i);

                // create new snake
                int x = rand() % map.n; // location
                int y = rand() % map.m; // location
                map.snakes.push_back(new Snake(x, y, &map));
            }
        }

        map.print();
        usleep(50000);
    }

    std::cout << "Game is finished";

    return 0;
}

