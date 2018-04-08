#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <iostream>
#include <string>
#include <fstream>
#include "Rat.h"
#include "Wolf.h"
#include "Dog.h"
#include <map>


class Map {
 public:
    std::pair<int, int> get_size();
    int add_enemy(const std::string& name, const std::pair<int, int>& pos);
    int is_enemy_on_cell(const std::pair<int, int>& pos);
    Person* get_enemy(const std::pair<int, int>& pos);
    void delete_enemy(const std::pair<int, int>& pos);
    int read_Map_from_file(const std::string& path_to_file);

 private:
    std::pair<int, int> size;
    std::map <std::pair<int, int>, class Person*> location_person;
};


#endif  // PROJECT_INCLUDE_MAP_H_
