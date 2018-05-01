#include "Map.h"
#include <iostream>
#include <fstream>
#include "Rat.h"
#include "Wolf.h"
#include "Dog.h"
#include "Armor.h"
#include "Helmet.h"
#include "Pants.h"
#include "Shield.h"
#include "T_Shirt.h"


std::pair<int, int> Map::get_size() {
    return size;
}

void Map::add_entity(const std::string& name, const std::pair<int, int>& pos) {
    if (name == "wolf") {
        location_entity.insert({pos, new Wolf(pos)});
        return;
    }
    if (name == "dog") {
        location_entity.insert({pos, new Dog(pos)});
        return;
    }
    if (name == "rat") {
        location_entity.insert({pos, new Rat(pos)});
        return;
    }
    if (name == "armor") {
        location_entity.insert({pos, new Armor(pos)});
        return;
    }
    if (name == "helmet") {
        location_entity.insert({pos, new Helmet(pos)});
        return;
    }
    if (name == "shield") {
        location_entity.insert({pos, new Shield(pos)});
        return;
    }
    if (name == "pants") {
        location_entity.insert({pos, new Pants(pos)});
        return;
    }
    if (name == "T-Shirt") {
        location_entity.insert({pos, new T_Shirt(pos)});
    }

    return;
}

/*void Map::add_entity(const char* name, const std::pair<int, int>& pos) {
    switch (name) {
        case "wolf": location_entity.insert({pos, new Wolf(pos)});
            break;
        case "dog": location_entity.insert({pos, new Dog(pos)});
            break;
        case "rat": location_entity.insert({pos, new Rat(pos)});
            break;
        case "armor": location_entity.insert({pos, new Armor(pos)});
            break;
        case "helmet": location_entity.insert({pos, new Helmet(pos)});
            break;
        case "shield": location_entity.insert({pos, new Shield(pos)});
            break;
        case "pants": location_entity.insert({pos, new Pants(pos)});
            break;
        case "T-Shirt": location_entity.insert({pos, new T_Shirt(pos)});
            break;
        default:
            break;
    }

    return;
}*/


bool Map::is_entity_on_cell(const std::pair<int, int>& pos) {
    return location_entity.find(pos) != location_entity.end();
}

Entity* Map::get_entity(const std::pair<int, int>& pos) {
    return location_entity[pos];
}


void Map::delete_entity(const std::pair<int, int>& pos) {
    int type = location_entity[pos]->get_type();
    if (type == ENEMY) {
        delete(static_cast<Enemy*>(location_entity[pos]));
    } else {
        if (type == ITEM) {
            delete(static_cast<Item*>(location_entity[pos]));
        }
    }
    location_entity.erase(pos);
}

void Map::transfer_to_person(std::pair<int, int> pos) {
    location_entity.erase(pos);
}

int Map::read_from_file(const std::string& path_to_file) {
    std::string name_object;
    std::ifstream in(path_to_file);
    int x = 0;
    int y = 0;

    if (in.bad()) {
        return -1;
    }

    in >> size.first >> size.second;
    while (in >> x >> y >> name_object) {
        add_entity(name_object, {x, y});
    }

    in.close();

    return 0;
}
