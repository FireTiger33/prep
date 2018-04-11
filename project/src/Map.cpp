#include "Map.h"


std::pair<int, int> Map::get_size() {
    return size;
}

bool Map::add_entity(const std::string& name, const std::pair<int, int>& pos) {
    if (name == "wolf") {
        location_entity.insert({pos, new Wolf(pos)});
        return 0;
    }
    if (name == "dog") {
        location_entity.insert({pos, new Dog(pos)});
        return 0;
    }
    if (name == "rat") {
        location_entity.insert({pos, new Rat(pos)});
        return 0;
    }
    if (name == "armor") {
        location_entity.insert({pos, new Armor(pos)});
        return 0;
    }
    if (name == "helmet") {
        location_entity.insert({pos, new Helmet(pos)});
        return 0;
    }
    if (name == "shield") {
        location_entity.insert({pos, new Shield(pos)});
        return 0;
    }
    if (name == "pants") {
        location_entity.insert({pos, new Pants(pos)});
        return 0;
    }
    if (name == "T-Shirt") {
        location_entity.insert({pos, new T_Shirt(pos)});
    }

    return 0;
}


int Map::is_entity_on_cell(const std::pair<int, int>& pos) {
    if (location_entity.find(pos) != location_entity.end()) {
        return 1;
    }

    return 0;
}

Entity* Map::get_entity(const std::pair<int, int>& pos) {
    return location_entity[pos];
}


void Map::delete_entity(const std::pair<int, int>& pos) {
    std::string type = location_entity[pos]->get_type();
    if (type == "enemy") {
        delete(static_cast<Enemy*>(location_entity[pos]));
    } else {
        if (type == "item") {
            delete(static_cast<Item*>(location_entity[pos]));
        }
    }
    location_entity.erase(pos);
}

void Map::transfer_to_person(std::pair<int, int> pos) {
    location_entity.erase(pos);
}

int Map::read_Map_from_file(const std::string& path_to_file) {
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
