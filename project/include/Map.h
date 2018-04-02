#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include "Rat.h"
#include "Wolf.h"
#include "Dog.h"
#include <map>


class Map {
public:
    Map () {

    }

    ~Map() {
        for (int i = 0; i < size.first; ++i) {
            free(map[i]);
        }
        free(map);
    }

    std::pair<int, int> get_size();
    int add_enemy (const std::string name, std::pair<int, int> pos);
    int add_enemy_on_map (const std::string name);
    int read_Map_from_file (const char* path_to_file);
    void print ();
    int is_enemy_on_cell(std::pair<int, int> pos);
    Person* get_enemy(std::pair<int, int> pos);
    void delete_enemy(std::pair<int, int> pos);
    int blank_map();

private:
    std::pair<int, int> size;
    int** map;
    std::map <std::pair<int, int>, class Person*> location_person;
};


#endif //PROJECT_MAP_H