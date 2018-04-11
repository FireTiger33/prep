#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Rat.h"
#include "Wolf.h"
#include "Dog.h"
#include "Entity.h"
#include "Item.h"


class Map {
 public:
    ~Map() {
        for (auto i = location_entity.begin(); i != location_entity.end(); i = location_entity.begin()) {
            delete_entity(i->first);
        }
    }

    std::pair<int, int> get_size();
    bool add_entity(const std::string& name, const std::pair<int, int>& pos);
    int is_entity_on_cell(const std::pair<int, int>& pos);
    Entity* get_entity(const std::pair<int, int>& pos);
    void delete_entity(const std::pair<int, int>& pos);
    void transfer_to_person(std::pair<int, int> pos);
    int read_Map_from_file(const std::string& path_to_file);

 private:
    std::pair<int, int> size;
    std::map<std::pair<int, int>, class Entity*> location_entity;
};


#endif  // PROJECT_INCLUDE_MAP_H_
